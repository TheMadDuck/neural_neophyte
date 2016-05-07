import numpy as np
import math as mt

import AIenvironment as AIEnv

def naiveElo(leftValue, rightValue, decition):
    distance = abs(leftValue - rightValue)
    normedDistance = (distance/5 + 0.1)
    if(decition == 1):
        normedDistance = - normedDistance
    leftValue += normedDistance
    rightValue -= normedDistance
    return (leftValue, rightValue)


def turnier(amountGames, bestModelExist):
    for game in range(amountGames):
        AIEnv.gameFlow([bestModelExist, bestModelExist])
    return 0
#bMap = {"synn": 1, "maij": 1}

#updatedElos = naiveElo(1.0, 2.0, 1)
#print(updatedElos)
