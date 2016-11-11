import numpy as np
import copy
#########################################
# save the game in a saveList

#init saveList
def initSaveList(transponiert):
    if transponiert: # data in form ((X,y), (X,y),(...)) 
        playerOne = []  #dürfen nur einmal initialisiert werden!
        playerTwo = []
        saveList = np.empty(2, dtype=np.object)
        saveList[:] = playerOne, playerTwo
        return saveList
    else: # data in form ((X,X,X...), (y,y,y...))
        playerOne = [[],[]]
        playerTwo = [[],[]]
        saveList = np.empty(2, dtype=np.object)
        saveList[:] = playerOne, playerTwo
        return saveList

def savePositions(field, color, roundNumber, position, saveList, transponiert):

    fieldCopy = copy.deepcopy(field)
    if transponiert: # data in form ((X, y), (X,y),(...))
        touple = (fieldCopy, position)
        if color == 1:
            saveList[0].append(touple) #TODO Testen!!!)
            return saveList
        else:
            saveList[1].append(touple)
            return saveList
    else: # data in form ((X,X,X...), (y,y,y...))
        if color == 1:
            flatField = fieldCopy.flatten()     # Achtung: flattne macht deepcopy. für ne einfache reference benutze ravel()... <- testen
            flatField = np.append(flatField, 1) # Achtung: habe ein feature für den jeweiligen player angehängt. 1 (bzw.2) ok ???
            flatField = np.append(flatField, roundNumber) 
            saveList[0][0].append(flatField)
            saveList[0][1].append(position)
            return saveList
        else:
            flatField = fieldCopy.flatten()     # Achtung: flattne macht deepcopy. für ne einfache reference benutze ravel()... <- testen
            flatField = np.append(flatField, 2)
            flatField = np.append(flatField, roundNumber) 
            saveList[1][0].append(flatField)
            saveList[1][1].append(position)
            return saveList
