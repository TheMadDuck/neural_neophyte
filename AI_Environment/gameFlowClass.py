'''
The AI environment. This file provides the game functionality for the neural network. It loads the necessary game functions and provides the gamefield + all game information to the net. You could say that it is the link between the game and the AI.

'''

import numpy as np
import random as rd
import pickle
import os.path


#########################################
#import minMax heuristics
import minMaxPruning


#########################################
import saveListHandler

#########################################

class gameFlowClass(object):
    #classifier = None
    #subPr = None


    ########################################
    # TODO: winner is global variable. maybe i should rebuild this file as a class ?!
    winner = None

    def __init__(self, extClassifier, extSubPr):
        #global classifier           
        self.classifier = extClassifier
        #global subPr
        self.subPr = extSubPr

    #best_models = None


    #########################################
    # naive AI:
    def AI_Move(self, field, playerNumber, roundNumber, legalMoves, classifierModel, randomMoveProba, saveTheGame):
        # sometimes you want a random move:
        if (rd.random() < randomMoveProba): 
            classifierModel = 0

        if(classifierModel):
            flatField = field.flatten()        
            flatField = np.append(flatField, playerNumber)
            flatField = np.append(flatField, roundNumber)
             
            if (saveTheGame == True):
                minMaxPruning.mcts(field, None, None, self.classifier, classifierModel, classifierModel, roundNumber, 0.2)
           

            return self.classifier.predict(flatField, classifierModel-1)[0]
        else: # random move:
            return rd.choice(legalMoves)

    #########################################
    #similar the human move:
    def Human_Move(self, legalMoves):
        move = int(input("wich move do you want to make? [" + str(legalMoves) + " ]"))
        return move




    #########################################
    # virtual game flow:

    #def gameFlow(player):   #TODO vieleicht eher sowas wie gameFlow(player1, player2) human:-1 random:0 ai models:1-x [allerdings sollten die models extern geladen werden...)   ACHTUNG ! ! ! noch spielt jedes model immer gegen sich selbst (bestmodel vs bestmodel) das sollte nicht sein !!
        #TODO field mit in die gameflow()-init. um mit nem nicht-leeren feld anzufangen. + bool um zu sagen ob spiel gesaved wird oder nicht.
    def gameFlow(self, player, field = None, saveTheGame = True, roundNumber = 0):
        amountRandom = 0.15  # vieleicht ausserhalb definieren?
        legalInputs = self.subPr.getLegalInputs()
        if self.subPr.getSignal() != "legalInputs_initialized":
            print("ERROR: legal Inputs could not get initialized")

        if (saveTheGame):
            saveList = saveListHandler.initSaveList(False)
        else:
            gamePath = [] # TODO: überlegen ob wenn wir zb monte-carlo benutzten wir nur den pfad benötigen

        if (field == None): #testen
            field = self.subPr.initField()
            if self.subPr.getSignal() != "field_initialized":
                print("ERROR: Field could not get initialized")

        while((self.subPr.getSignal() != "weHaveAWinner") or (self.subPr.getSignal() != "gameIsOver")):
            roundNumber += 1
            if roundNumber % 2 == 1:
                playerNumber = 1
            else:
                playerNumber = 2
                
            if (player[playerNumber-1] == -1):
                position = self.Human_Move(legalInputs)
            else:
                position = self.AI_Move(field, playerNumber, roundNumber, legalInputs, player[playerNumber-1], amountRandom, saveTheGame)

            self.subPr.isLegalMove(field, playerNumber, position)

            while (self.subPr.getSignal() == "unvalidPlayer") or (self.subPr.getSignal() == "unvalidPosition" or self.subPr.getSignal() == "columnIsFull"):
                if (player[playerNumber-1] == -1):
                    print("this move is not legal, please try again!!")
                    position = self.Human_Move(legalInputs)
                else:
                    position = self.AI_Move(field, playerNumber, roundNumber, legalInputs, False, amountRandom, saveTheGame)

                self.subPr.isLegalMove(field, playerNumber, position)
                #print(field)
            

            if(saveTheGame):
                saveList = saveListHandler.savePositions(field, playerNumber, roundNumber, position, saveList, False)   #TODO : information wer gerade am zug ist abspeichern und providen. entweder jedes mal field invertieren oder ein feature mehr reintun.!!! 
            else:
                gamePath.append(position)

            self.subPr.setStone(field, playerNumber, position)
            if self.subPr.getSignal() != "stoneIsSet":
                print("ERROR: Stone is not saved")
            if(player[0] == -1 or player[1] == -1): #TODO für jede phase einzeln testen
                print(" ")
                print(field)        # show field in a game vs. a human !!!
            global winner
            winner = self.subPr.hasAWinner(field, playerNumber, position)
            if (self.subPr.getSignal() == "weHaveAWinner"):
                if winner == 0:
                    print("ERROR: we could not determine who won!")
                if(player[0] == -1 or player[1] == -1):
                    print(" ")
                    print("the winner is: " + str(winner))
                    print(" ")
                break
            
            self.subPr.gameStopped(field, roundNumber)
            if (self.subPr.getSignal() == "gameIsOver"):
                break

        if(saveTheGame):
            return saveList[winner-1]
        else:
            return gamePath  # returns only the path, the game took [do we need information about the  winner?]

    def getWinner(self):
        return winner




############################################

# TODO: do i realy need this and the fourInARow file as classes? Compare speed with non-class version( there i have to make a deepcopy of field in the mcts function, and i have to put the roundNumber-variable into the gameflow()init. furthermore there is still an error with the roundnumber...
# change name (AI_environment.py)
#TODO add documentation!!!
#TODO integrate the MLP. 
#TODO human vs Ai mode basteln. (hier oder extern?)
#TODO always keep the X-best Models [X = 5 or ?], so AI-Move can choose from a set of models. <- git exclude one folder with models???!!!!!!!!
#     mayby rank those with an elo number?! 
#TODO Elo tunier. (count when an older modelling beat an younger?) higher elo -> higher probability to play! Which model plays against which model in train phase? train phase trough turnier?
#TODO rewrite entire code in c
#TODO enjoy life


###########################################



'''
# more possible signals:
    if subPr.getSignal() == "processing":
        continue
    if subPr.getSignal() == "ended":
        break
    if subPr.getSignal() == "gameStopped":
        print ("game stopped")
        break
    if subPr.getSignal() == "makeMove":
        print("i should make a move")
    if subPr.getSignal() == "iHaveASolution":
        subPr.printSaveList()

    if roundNumber > 24:
        print("break to provoke endless loop")
        print("code is probably not yet 'vollendet'")
        break

'''




