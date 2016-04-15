'''
a template for a game. In this case the famous game 'four in a line' or in this case 'four in a row'. you have to asure that the functions.........   and the  SIGNAL's ........... are provided.
'''
import numpy as np
import copy

SIGNAL = ""

def getSignal():
    global SIGNAL
    return SIGNAL

def getLegalInputs():
    global SIGNAL
    SIGNAL = "legalInputs_initialized"
    return [0,1,2,3,4,5,6]

def initField():
    field= np.zeros((7, 7), dtype=int) # game field is 6 high and 7 wide, but we need a bottom row. so the stones dont fall through the game
    field[field.shape[0]-1][:] = 3         # bottom row
    global SIGNAL
    SIGNAL = "field_initialized"
    return field

def isLegalMove(field, playerNumber, position):
    
    if (playerNumber != 1) and (playerNumber != 2):
        print (str(playerNumber) + " is a unvalid player")
        global SIGNAL
        SIGNAL = "unvalidPlayer"
        return False
    if position < 0 or position > field.shape[1]-1:
        print (str(position) + " is a unvalid position")
        global SIGNAL
        SIGNAL = "unvalidPosition"
        return False
    #print(field.shape)
    if field[0][position] != 0:
        print("column is full, please choose again!")
        global SIGNAL
        SIGNAL = "columnIsFull"
        #return None
        return False
    global SIGNAL
    SIGNAL = "moveIsLegal"
    return True

def setStone(field, color, position):
    for i in range(field.shape[0]):
        if field[i][position] != 0:
            field[i-1][position] = color
            break

    global SIGNAL
    SIGNAL = "stoneIsSet"
    return field

def gameStopped(field, roundNumber):
    print (field.size - field.shape[1])
    print (roundNumber)
    if roundNumber == (field.size - field.shape[1]):
        print("you played a draw")
        global SIGNAL
        SIGNAL = "gameIsOver"
        return 1

def hasAWinner(field, color, position):
    inALine = 0
    #check depth of the new stone:
    depth = 0
    for i in range(field.shape[0]):
        if field[i][position] == 0:
            depth += 1
        else:
            break
    #column check:
    #TODO die range hier von depth bis field.shape[0] und testen
    for i in range(field.shape[0]): 
        if field[i][position] == 0:
            continue    
        if field[i][position] == color:
            inALine += 1
        else:
            break

    if inALine >= 4:
        global SIGNAL
        SIGNAL = "weHaveAWinner"
        return color
    #TODO testen
    #row check:
    inALine = 0
    for i in range(field.shape[1]):
        if field[depth][i] == color:
            inALine += 1
        else:
            inALine = 0
        if inALine >= 4:
            global SIGNAL
            SIGNAL = "weHaveAWinner"
            return color
    #TODO    
    #diagonal checks:
    inALineUp = 0
    inALineDown = 0
    topLeftStart = depth - position
    bottomLeftStart = depth + position
    for i in range(field.shape[1]):
        if (topLeftStart >= 0) and (topLeftStart < field.shape[0]):
            if field[topLeftStart][i] == color:
                inALineUp += 1
            else:
                inALineUp = 0
            if inALineUp >= 4:
                global SIGNAL
                SIGNAL = "weHaveAWinner"
                return color
        topLeftStart += 1

        if (bottomLeftStart >= 0) and (bottomLeftStart < field.shape[0]):
            if field[bottomLeftStart][i] == color:
                inALineDown += 1
            else:
                inALineDown = 0
            if inALineDown >= 4:
                global SIGNAL
                SIGNAL = "weHaveAWinner"
                return color
        bottomLeftStart -= 1
        
    return 0

'''
def initSaveList():
    playerOneField = []  #dürfen nur einmal initialisiert werden!
    playerTwoField = []
    playerOnePosition = []
    playerTwoPosition = []
    #saveList = np.array((playerOneField, playerTwoField, playerOnePosition, playerTwoPosition))
    saveList = np.empty(4, dtype=np.object)
    saveList[:] = playerOneField, playerTwoField, playerOnePosition, playerTwoPosition
    print (saveList)
    return saveList

#TODO
def savePositions(field, color, position, saveList):

    fieldCopy = copy.deepcopy(field)
    if color == 1:
        saveList[0].append(fieldCopy) #TODO Testen!!!
        saveList[2].append(position)
        return saveList
    else:
        saveList[1].append(fieldCopy)
        saveList[3].append(position)
        return saveList
'''

def initSaveList():
    playerOne = []  #dürfen nur einmal initialisiert werden!
    playerTwo = []
    saveList = np.empty(2, dtype=np.object)
    saveList[:] = playerOne, playerTwo
    global SIGNAL
    SIGNAL = "saveList_initialized"
    return saveList

def savePositions(field, color, position, saveList):

    fieldCopy = copy.deepcopy(field)
    touple = (fieldCopy, position)
    if color == 1:
        saveList[0].append(touple) #TODO Testen!!!)
        global SIGNAL
        SIGNAL = "positionSaved"
        return saveList
    else:
        saveList[1].append(touple)
        global SIGNAL
        SIGNAL = "positionSaved"
        return saveList

def playGame():
    saveList = initSaveList()
    field = initField()
    roundNumber = 0
    while (not gameStopped(field, roundNumber)):
        roundNumber += 1
        if roundNumber % 2 == 0:
            color = 2
        else:
            color = 1
        position = int(input("Player " + str(color) + " please choose a row: "))
        while (not isLegalMove(field, color, position)):
            position = int(input("Player " + str(color) + " please choose a row: "))
        saveList = savePositions(field, color, position, saveList)
        setStone(field, color, position)
        print(field)
        if hasAWinner(field, color, position) != 0:
            print("congratulations")
            break
    #TODO show savePositions
    print (saveList)

def gameLoop():
    return

def main():
    playGame()

#main()
