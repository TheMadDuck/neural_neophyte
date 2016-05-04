#import numpy as np

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
