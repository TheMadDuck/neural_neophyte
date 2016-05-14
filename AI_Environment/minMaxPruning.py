#import numpy as np
import AIenvironment
import gameFlowClass as gFC
import games.fourInARow as gL
import copy

"""
def minmax(position, depth):
    if position = won:
        return 1
    else if(position = lost):
        return -1
    else:
        return 0
    
    if depth == 0;
        return evalScore

    bestScore = -99999999

    for move in possibleMoves:
        subScore = -minmax(position(mitMove) , depth -1)
        if subScore > bestScore:
            bestScore = subScore

    return bestScore


# oder so... :P
"""

def mcts(field, tree, legalMoves, classifier, playerOne, playerTwo, roundNumber, randomMoveProba):
    
#    path = AIenvironment.gameFlow([playerOne, playerTwo], field, False)
    fieldCopy = copy.deepcopy(field)
    tempGameLogic = gL.gameLogic()
    tempGameFlow = gFC.gameFlowClass(classifier, tempGameLogic) # TODO: siehe todo nächste zeile...
#    tempGameFlow.setImports(classifier, tempGameLogic) #TODO hier nicht nur player one imorten ?!
    path = tempGameFlow.gameFlow([playerOne, playerTwo], fieldCopy, False, roundNumber)
    del fieldCopy
    del tempGameLogic
    del tempGameFlow
    return 0

