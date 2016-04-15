import random as rd

#########################################
#load game:

import fourInARow as subPr


#########################################
# naive AI:
def naiveAI(legalMoves):
    return rd.choice(legalMoves)

# onl
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

game = subPr.gameLoop()
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
    print("now my signal is: ")
    print(subPr.getSignal())
    if subPr.getSignal() == "moveIsLegal":
        saveList = subPr.savePositions(field, playerNumber, position, saveList)    
    if subPr.getSignal() != "positionSaved":
        print("ERROR: Position could not get saved")

    subPr.setStone(field, playerNumber, position)
    if subPr.getSignal() != "stoneIsSet":
        print("ERROR: Stone is not saved")
    
    print(field)
    
    subPr.hasAWinner(field, playerNumber, position)
    if (subPr.getSignal() != "weHaveAWinner"):
        break
    
    subPr.gameStopped(field, roundNumber)

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
def playFourInARow():
    saveList = fourInARow.initSaveList()
    field = fourInARow.initField()
    roundNumber = 0
    while (not fourInARow.gameStopped(field, roundNumber)):
        roundNumber += 1
    if roundNumber % 2 == 0:
        color = 2
    else:
        color = 1
        position = int(input("Player " + str(color) + " please choose a row: "))
        while (not fourInARow.isLegalMove(field, color, position)):
            position = int(input("Player " + str(color) + " please choose a row: "))
        saveList = fourInARow.savePositions(field, color, position, saveList)
        fourInARow.setStone(field, color, position)
        print(field)
        if fourInARow.hasAWinner(field, color, position) != 0:
            print("congratulations")
            break
    print (saveList)
'''




