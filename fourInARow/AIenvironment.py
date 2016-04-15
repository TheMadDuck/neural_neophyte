import fourInARow as subPr

saveList = subPr.initSaveList()
if subPr.getSignal() != "saveList_initialized":
    print("ERROR: SaveList could not get initialized")

field = subPr.initField()
if subPr.getSignal() != "field_initialized":
    print("ERROR: Field could not get initialized")

game = subPr.startGameLoop()
roundNumber = 0
while(True):
    roundNumber += 1
    if roundNumber % 2 == 1:
        playerNumber = 1
    else:
        playerNumber = 2
    position = 345245 # get new position from extern
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

legalInputs = [0,1,2,3,4,5,6]
