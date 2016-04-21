'''
The AI environment. This file provides the game functionality for the neural network. It loads the necessary game functions and provides the gamefield + all game information to the net. You could say that it is the link between the game and the AI.

'''

import numpy as np
import random as rd
import pickle

########################################
#load classifier:
import logistic_sgd as classifier


#########################################
#load game:

import fourInARow as subPr


#########################################
# naive AI:
def naiveAI(legalMoves):
    return rd.choice(legalMoves)


#########################################
# virtual game flow:

def gameFlow():
    legalInputs = subPr.getLegalInputs()
    if subPr.getSignal() != "legalInputs_initialized":
        print("ERROR: legal Inputs could not get initialized")

    saveList = subPr.initSaveList()
    if subPr.getSignal() != "saveList_initialized":
        print("ERROR: SaveList could not get initialized")

    field = subPr.initField()
    if subPr.getSignal() != "field_initialized":
        print("ERROR: Field could not get initialized")


    #game = subPr.gameLoop()
    roundNumber = 0
    while((subPr.getSignal() != "weHaveAWinner") or (subPr.getSignal() != "gameIsOver")):
        roundNumber += 1
        if roundNumber % 2 == 1:
            playerNumber = 1
        else:
            playerNumber = 2

        position = naiveAI(legalInputs) # get new position from extern
        subPr.isLegalMove(field, playerNumber, position)
        while (subPr.getSignal() == "unvalidPlayer") or (subPr.getSignal() == "unvalidPosition" or subPr.getSignal() == "columnIsFull"):
            position = naiveAI(legalInputs) # get new position from extern
            subPr.isLegalMove(field, playerNumber, position)
        if subPr.getSignal() != "moveIsLegal":
            print("ERROR: The AI-Environment could not make a legal move")
        saveList = subPr.savePositions(field, playerNumber, position, saveList)    
        if subPr.getSignal() != "positionSaved":
            print("ERROR: Position could not get saved")

        subPr.setStone(field, playerNumber, position)
        if subPr.getSignal() != "stoneIsSet":
            print("ERROR: Stone is not saved")
        
        print(field)
        winner = subPr.hasAWinner(field, playerNumber, position)
        if (subPr.getSignal() == "weHaveAWinner"):
            print("we have a winner!!!")
            if winner == 0:
                print("ERROR: we could not determine who won!")
            print("the winner is: " + str(winner))
            break
        
        subPr.gameStopped(field, roundNumber)

    print("################################")
    print("spielverlauf vom Sieger (zum lernen):")
    print(saveList[winner-1])
    return saveList[winner-1]

# change name (AI_environment.py)
#TODO add documentation!!!
#TODO four in a row still does not provide informations about the winner. 
#TODO integrate the NN. 
#TODO enjoy life


def getTrainTestValidate(numberTrain, numberTest, numberValidate, KIone, KItwo):
    """
    get the winning moves of many games (KIone vs. KItwo)
    """
    winnerPoolTrain = []
    for i in range(numberTrain):
        winnerPoolTrain.append(gameFlow())

    winnerPoolTest = []
    for i in range(numberTest):
        winnerPoolTest.append(gameFlow())

    winnerPoolValidate = [] 
    for i in range(numberValidate):
        winnerPoolValidate.append(gameFlow())


    dataset = np.array((winnerPoolTrain, winnerPoolTest, winnerPoolValidate))   ## gucken wie dataset auszusehen hat, villeicht auch ([],(),[[]]....

    #TODO wirklich pickln?
#    newFile= open("gameTTV.p", "w+")
    pickle.dump(dataset, open("gameTTV.p", "rb"))
    return dataset


getTrainTestValidate(10,10,10,"hans", "peter")

############################################

classifier.sgd_optimization(learning_rate=0.13, n_epochs=1000, dataset=winnerSave.pkl, batch_size=600)






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




