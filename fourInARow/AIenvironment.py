'''
The AI environment. This file provides the game functionality for the neural network. It loads the necessary game functions and provides the gamefield + all game information to the net. You could say that it is the link between the game and the AI.

'''


import random as rd
#########################################
#load game:

import fourInARow as subPr


#########################################
# naive AI:
def naiveAI(legalMoves):
    return rd.choice(legalMoves)


#########################################
# virtual game flow:


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
    subPr.hasAWinner(field, playerNumber, position)
    if (subPr.getSignal() == "weHaveAWinner"):
        print("we have a winner!!!")
        break
    
    subPr.gameStopped(field, roundNumber)


# change name (AI_environment.py)
#TODO add documentation!!!
#TODO four in a row still does not provide informations about the winner. 
#TODO integrate the NN. 
#TODO enjoy life


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




