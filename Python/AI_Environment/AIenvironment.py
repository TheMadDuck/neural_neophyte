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
classifier = None
subPr = None


########################################
# TODO: winner is global variable. maybe i should rebuild this file as a class ?!
winner = None

def setImports(extClassifier, extSubPr):
    global classifier           
    classifier = extClassifier
    global subPr
    subPr = extSubPr

#best_models = None


#########################################
# the AI:
def AI_Move(field, playerNumber, roundNumber, legalMoves, classifierModel, randomMoveProba, saveTheGame):
    # sometimes you want a random move:
    if (rd.random() < randomMoveProba): 
        classifierModel = 0

    if(classifierModel):
        #TODO WICHTIG:  field glätten und in flatfield speichern

        #fieldCopy = copy.deepcopy(field)

        #print("A I")
        flatField = field.flatten()        
        flatField = np.append(flatField, playerNumber)
        flatField = np.append(flatField, roundNumber)
        '''
        if (saveTheGame == True):
            print("test: saveGame = True")
            minMaxPruning.mcts(field, None, None, classifierModel, classifierModel, 0.2)
        else:
            print("test: saveGame =  False!")
        '''
        return classifier.predict(flatField, classifierModel-1)[0]
    else:
        #print("random")
        return rd.choice(legalMoves)

#########################################
#similar the human move:
def Human_Move(legalMoves):
    move = int(input("wich move do you want to make? [" + str(legalMoves) + " ]"))
    return move




#########################################
# virtual game flow:

#def gameFlow(player):   #TODO vieleicht eher sowas wie gameFlow(player1, player2) human:-1 random:0 ai models:1-x [allerdings sollten die models extern geladen werden...)   ACHTUNG ! ! ! noch spielt jedes model immer gegen sich selbst (bestmodel vs bestmodel) das sollte nicht sein !!
    #TODO field mit in die gameflow()-init. um mit nem nicht-leeren feld anzufangen. + bool um zu sagen ob spiel gesaved wird oder nicht.
def gameFlow(player, field = None, saveTheGame = True):
    amountRandom = 0.15  # vieleicht ausserhalb definieren?
    legalInputs = subPr.getLegalInputs()
    if subPr.getSignal() != "legalInputs_initialized":
        print("ERROR: legal Inputs could not get initialized")

    if (saveTheGame):
        saveList = saveListHandler.initSaveList(False)
    else:
        gamePath = [] # TODO: überlegen ob wenn wir zb monte-carlo benutzten wir nur den pfad benötigen

    if (field == None): #testen
        field = subPr.initField()
        if subPr.getSignal() != "field_initialized":
            print("ERROR: Field could not get initialized")

    roundNumber = 0
    while((subPr.getSignal() != "weHaveAWinner") or (subPr.getSignal() != "gameIsOver")):
        roundNumber += 1
        if roundNumber % 2 == 1:
            playerNumber = 1
        else:
            playerNumber = 2
        if (player[playerNumber-1] == -1):
            position = Human_Move(legalInputs)
        else:
            position = AI_Move(field, playerNumber, roundNumber, legalInputs, player[playerNumber-1], amountRandom, saveTheGame) # get new position from extern
        subPr.isLegalMove(field, playerNumber, position)


        while (subPr.getSignal() == "unvalidPlayer") or (subPr.getSignal() == "unvalidPosition" or subPr.getSignal() == "columnIsFull"):
            if (player[playerNumber-1] == -1): # is the human player 1 or player 2?
                print("this move is not legal, please try again!!")
                position = Human_Move(legalInputs)
            else:
                #print("ERROR: The AI-Environment could not make a legal move. will try random move..")
                position = AI_Move(field, playerNumber, roundNumber, legalInputs, False, amountRandom, saveTheGame) # get new position from extern
            subPr.isLegalMove(field, playerNumber, position)


        if(saveTheGame):
            saveList = saveListHandler.savePositions(field, playerNumber, roundNumber, position, saveList, False)   #TODO : information wer gerade am zug ist abspeichern und providen. entweder jedes mal field invertieren oder ein feature mehr reintun.!!! 
        else:
            gamePath.append(position)
            #TODO komplette savelist logic in die classe hier?!

        subPr.setStone(field, playerNumber, position)
        if subPr.getSignal() != "stoneIsSet":
            print("ERROR: Stone is not saved")
        if(player[0] == -1 or player[1] == -1): #TODO für jede phase einzeln testen
            print(" ")
            print(field)        # show field in a game vs. a human !!!
        global winner
        winner = subPr.hasAWinner(field, playerNumber, position)
        if (subPr.getSignal() == "weHaveAWinner"):
            if winner == 0:
                print("ERROR: we could not determine who won!")
            if(player[0] == -1 or player[1] == -1):
                print(" ")
                print("the winner is: " + str(winner))
                print(" ")
            break
        
        subPr.gameStopped(field, roundNumber)
        if (subPr.getSignal() == "gameIsOver"):
            break

    if(saveTheGame):
        return saveList[winner-1]
    else:
        return gamePath  # returns only the path, the game took [do we need information about the  winner?]

def getWinner():
    return winner




############################################


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




