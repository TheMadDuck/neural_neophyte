import numpy as np
import math as mt
import random as rd

import AIenvironment as AIEnv

def naiveElo(leftValue, rightValue, decition):
    distance = abs(leftValue - rightValue)
    normedDistance = (distance/5 + 0.1)
    if(decition == 1):
        normedDistance = - normedDistance
    leftValue += normedDistance
    rightValue -= normedDistance
    return (leftValue, rightValue)


def turnier(amountGames, amountModels):
    for game in range(amountGames):
        KI_One = rd.randint(0, amountModels) # besser vieleicht:  abs(normalverteilt(-KI_Number, + KI_Number))
        KI_Two = rd.randint(0, amountModels)
        AIEnv.gameFlow([KI_One, KI_Two])
    return 0
#bMap = {"synn": 1, "maij": 1}

#updatedElos = naiveElo(1.0, 2.0, 1)
#print(updatedElos)
