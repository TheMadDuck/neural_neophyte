import random as rd
import numpy as np

def nRand(border): #returns a integer beween 0 and border(booth inclusive). 0 is the least probable
    if border == 0:
        return 0
    norm = np.random.normal(border, border/3, 1)
    norm = norm.astype(int)
    norm = abs(norm)
    sizeNorm = norm.size
    for i in range(sizeNorm):
        if norm[i] >= border:# > testen???
            norm[i] = rd.randint(0, border-1)
    return norm[0]
