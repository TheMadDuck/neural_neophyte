'''
The AI environment. This file provides the game functionality for the neural network. It loads the necessary game functions and provides the gamefield + all game information to the net. You could say that it is the link between the game and the AI.

'''

import numpy as np
import random as rd
import pickle
import os.path
import tree as tr

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
    #winner = None

    def __init__(self, extClassifier, extSubPr, field = None, roundNumber = 0,  amountRandom = 0.15, tree = tr.gameTree()): #TODO: maybe more inits?
        self.classifier = extClassifier
        self.subPr = extSubPr
        self.field = field
        self.roundNumber = roundNumber
        self.amountRandom = amountRandom
        self.winner = None
        self.tree = tree

    #best_models = None


    #########################################
    # naive AI:
    def AI_Move(self, playerNumber, legalMoves, players, randomMoveProba, saveTheGame):
        # sometimes you want a random move:
        if (rd.random() < randomMoveProba): 
            return rd.choice(legalMoves)
        # player 0 means random move:
        if (players[playerNumber-1] == 0):
            return rd.choice(legalMoves)

        flatField = self.field.flatten()        
        flatField = np.append(flatField, playerNumber)
        flatField = np.append(flatField, self.roundNumber)
         
        if (saveTheGame == True):
            #if one of the players is humans, minMaxPrunning should work with two AI_classifiers
            if (players[0] == -1):
                return minMaxPruning.exploited_mcts(self.field, self.tree, legalMoves, self.classifier, [players[1],players[1]], self.roundNumber, playerNumber, 0.2)
            if (players[1] == -1):
                return minMaxPruning.exploited_mcts(self.field, self.tree, legalMoves, self.classifier, [players[0],players[0]], self.roundNumber, playerNumber, 0.2)

            return minMaxPruning.exploited_mcts(self.field, self.tree, legalMoves, self.classifier, players, self.roundNumber, playerNumber, 0.2)

        return self.classifier.predict(flatField, players[playerNumber-1]-1)[0] # inner -1: because playerNumber is always 1 or 2, outer -1: because the models are named model0, model1, model2,... but the 0 is reserved for random. maybe i should make the -1 operation in the classifier class?!


    #########################################
    #similar the human move:
    def Human_Move(self, legalMoves):
        move = int(input("wich move do you want to make? [" + str(legalMoves) + " ]"))
        return move




    #########################################
    # virtual game flow:

    #def gameFlow(player):   #TODO vieleicht eher sowas wie gameFlow(player1, player2) human:-1 random:0 ai models:1-x [allerdings sollten die models extern geladen werden...)   ACHTUNG ! ! ! noch spielt jedes model immer gegen sich selbst (bestmodel vs bestmodel) das sollte nicht sein !!
        #TODO field mit in die gameflow()-init. um mit nem nicht-leeren feld anzufangen. + bool um zu sagen ob spiel gesaved wird oder nicht.
    def gameFlow(self, player, saveTheGame = True, prefixPath = []):
        if (saveTheGame):
            saveList = saveListHandler.initSaveList(False)
        else:
            gamePath = [] # TODO: überlegen ob wenn wir zb monte-carlo benutzten wir nur den pfad benötigen

        if prefixPath != []:
            preWinner = self.addPrefixPath(prefixPath)
            if (preWinner):
                gamePath.extend(prefixPath)
                return gamePath   #returnen 'TODO ja doch, oder?
        self.amountRandom = 0.15  # vieleicht ausserhalb definieren?
        #print(player)
        legalInputs = self.subPr.getLegalInputs()
        if self.subPr.getSignal() != "legalInputs_initialized":
            print("ERROR: legal Inputs could not get initialized")


        if (self.field == None): #testen
            self.field = self.subPr.initField()
            if self.subPr.getSignal() != "field_initialized":
                print("ERROR: Field could not get initialized")

        while((self.subPr.getSignal() != "weHaveAWinner") or (self.subPr.getSignal() != "gameIsOver")):
            if self.roundNumber % 2 == 0:
                playerNumber = 1
            else:
                playerNumber = 2
                
            if (player[playerNumber-1] == -1):
                position = self.Human_Move(legalInputs)
            else:
                position = self.AI_Move(playerNumber, legalInputs, player, self.amountRandom, saveTheGame)
            
            if (saveTheGame): #TODO ueberlegen ob das hier und in zeile 131 an der richtigen stelle ist.
                self.tree.cutRoot(position)
            self.subPr.isLegalMove(self.field, playerNumber, position)

            while (self.subPr.getSignal() == "unvalidPlayer") or (self.subPr.getSignal() == "unvalidPosition" or self.subPr.getSignal() == "columnIsFull"):
                self.subPr.gameStopped(self.field, self.roundNumber)
                if (self.subPr.getSignal() == "gameIsOver"):
                    break

                if (player[playerNumber-1] == -1):
                    print("this move is not legal, please try again!!")
                    position = self.Human_Move(legalInputs)
                else:
                    position = self.AI_Move(playerNumber, legalInputs, player, 1, saveTheGame)
                if (saveTheGame):
                    self.tree.cutRoot(position)

                self.subPr.isLegalMove(self.field, playerNumber, position)
                
                #print(field)
            

            if(saveTheGame):
                saveList = saveListHandler.savePositions(self.field, playerNumber, self.roundNumber, position, saveList, False)   #TODO : information wer gerade am zug ist abspeichern und providen. entweder jedes mal field invertieren oder ein feature mehr reintun.!!! 
            else:
                gamePath.append(position)

            self.subPr.setStone(self.field, playerNumber, position)
            if self.subPr.getSignal() != "stoneIsSet":
                print("ERROR: Stone is not saved")
            if(player[0] == -1 or player[1] == -1): #TODO für jede phase einzeln testen
                print(" ")
                print(self.field)        # show field in a game vs. a human !!!
            #global winner
            self.winner = self.subPr.hasAWinner(self.field, playerNumber, position)
            if (self.subPr.getSignal() == "weHaveAWinner"):
                if self.winner == 0:
                    print("ERROR: we could not determine who won!")
                if(player[0] == -1 or player[1] == -1):
                    print(" ")
                    print("the winner is: " + str(self.winner))
                    print(" ")
                break
            
            self.subPr.gameStopped(self.field, self.roundNumber)
            if (self.subPr.getSignal() == "gameIsOver"):
                break
            
            self.roundNumber += 1

        if(saveTheGame):
            return saveList[self.winner-1]
        else:
            #print("we should brake2")
            return gamePath  # returns only the path, the game took [do we need information about the  winner?]

    def getWinner(self):
        return self.winner

    def resetgame(self):
        self.field = None
        self.roundNumber = 0

    def addPrefixPath(self, prefixPath):    #TODO: diese funktion auf herz und nieren testen!
        
        prefixPathSize = len(prefixPath)
        pathPosition = 0
        while((self.subPr.getSignal() != "weHaveAWinner") or (self.subPr.getSignal() != "gameIsOver")):
            if(pathPosition >= prefixPathSize):
                return
            if self.roundNumber % 2 == 0:
                playerNumber = 1
            else:
                playerNumber = 2
                
            position = prefixPath[pathPosition]
            self.subPr.isLegalMove(self.field, playerNumber, position)

            while (self.subPr.getSignal() == "unvalidPlayer") or (self.subPr.getSignal() == "unvalidPosition" or self.subPr.getSignal() == "columnIsFull"):
                return

                
            


            self.subPr.setStone(self.field, playerNumber, position)
            if self.subPr.getSignal() != "stoneIsSet":
                print("ERROR: Stone is not saved")
            self.winner = self.subPr.hasAWinner(self.field, playerNumber, position)
            if (self.subPr.getSignal() == "weHaveAWinner"):
                if self.winner == 0:
                    print("ERROR: we could not determine who won!")
                break
            
            self.subPr.gameStopped(self.field, self.roundNumber)
            if (self.subPr.getSignal() == "gameIsOver"):
                break
            self.roundNumber +=1
            pathPosition += 1
        return self.getWinner()


############################################

# TODO: do i realy need this and the fourInARow file as classes? Compare speed with non-class version( there i have to make a deepcopy of field in the mcts function, and i have to put the roundNumber-variable into the gameflow()init. furthermore there is still an error with the roundnumber...
# change name (AI_environment.py)
#TODO add documentation!!!
#TODO integrate the MLP. 
#TODO human vs Ai mode basteln. (hier oder extern?)
#TODO always keep the X-best Models [X = 5 or ?], so AI-Move can choose from a set of models. <- git exclude one folder with models???!!!!!!!!
#     mayby rank those with an elo number?! 
#TODO Elo tunier. (count when an older modelling beat an younger?) higher elo -> higher probability to play! Which model plays against which model in train phase? train phase trough turnier?
#TODO to prevent import errors (especially in c) gameFlow-class and mcts-class could be written in one file. even if we create a small gameFlow-class we can not get rid of the circular recursion [gameflow-mcts-smallGameflow-mcts-smallGameflow-...]
#TODO rewrite entire code in c/cpp
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




