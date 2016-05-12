import numpy as np
import math as mt
import random as rd
import pickle
import os
import shutil

import AIenvironment as AIEnv


#########################################
#import own random distrib
import nRandomDistrib.nRand as nRand

def naiveElo(leftValue, rightValue, decition):
    distance = abs(leftValue - rightValue)
    normedDistance = (distance/5 + 0.1)
    if(decition == 0): #played a draw #TODO: bei draw müssen die punkte anders verteilt werden. Was ist mit grossen punkte unterschieden?
        return (leftValue, rightValue)
    if(decition == 1):
        normedDistance = - normedDistance
    leftValue += normedDistance
    rightValue -= normedDistance
    return (leftValue, rightValue)

#########################################
#get elo-numbers from file
def loadEloFile(gameName):
    if (not os.path.isdir("./best_models")):
        os.makedirs("./best_models") # maybe in a try catch block
        print("best models is created")

#    gameName = subPr.getName()
    if (not os.path.isdir("./best_models/" + str(gameName))):
        os.makedirs("./best_models/" + str(gameName))
        print(str(gameName) + "-folder is created")
    eloFileName = None
    for file in os.listdir("./best_models/" + str(gameName)):
        if file.endswith(".txt"):
            eloFileName = ("./best_models/" + str(gameName) + "/" + str(file))
    
    print (eloFileName)
    if (eloFileName):
        eloFile = pickle.load(open(eloFileName, 'rb'))
    else:
        eloFile = None
    return eloFile



#########################################
#get elo-numbers from file
def saveEloFile(eloRanking, gameName):
    if (not os.path.isdir("./best_models")):
        os.makedirs("./best_models") # maybe in a try catch block
        print("best models is created")

#    gameName = subPr.getName()
    if (not os.path.isdir("./best_models/" + str(gameName))):
        os.makedirs("./best_models/" + str(gameName))
        print(str(gameName) + "-folder is created")
    
    eloFileName = ("./best_models/" + str(gameName) + "/" + "elo_ranking.txt")
    
    print (eloFileName)
    if (eloFileName):
        pickle.dump(eloRanking, open(eloFileName, 'wb'))
    return 0


################################################
def sortModels(eloRanking, gameName):
    newEloRanking = sorted(range(len(eloRanking)), key=lambda k: eloRanking[k])
    
    #to prevent that we overwrite existing files we have to make temp-files:
    for i in range(len(eloRanking)):
        shutil.copy2("./best_models/" + str(gameName) + "/best_model_" + str(i) + ".pkl", "./best_models/" + str(gameName) + "/temp_best_model_" + str(i) + ".pkl")
    
    #overwrite the old model-files with the sorted temp-files:
    for i in range(len(eloRanking)):
        shutil.move("./best_models/" + str(gameName) + "/temp_best_model_" + str(i) + ".pkl", "./best_models/" + str(gameName) + "/best_model_" + str(newEloRanking[i]) + ".pkl")  #wegen move gibt es jetzt keine temp_file mehr, und die alte best_model file wurde überschrieben !!?!

    return newEloRanking


#################################################
def turnier(amountGames, amountModels, gameName):

    #eloRanking = loadEloFile(gameName)  # brauchen wir wirklich die ergebniss vorheriger turniere??

    #if (eloRanking == None):
    eloRanking = [1000] * amountModels
    print(eloRanking)
    for game in range(amountGames):
        KI_One = nRand.nRand(amountModels)  #TODO checken: wenn amountModels > 1, wird dann je ein random model benutzt? kommt das random model überhaupt in das eloRanking model??
        KI_Two = nRand.nRand(amountModels)
        AIEnv.gameFlow([KI_One, KI_Two])
        newRanking = naiveElo(eloRanking[KI_One], eloRanking[KI_Two], AIEnv.getWinner())
        eloRanking[KI_One] = newRanking[0]
        eloRanking[KI_Two] = newRanking[1]

    #erst sortModels zum pkl datei umbenennen
    sortModels(eloRanking, gameName)
    eloRanking = sorted(eloRanking)
    #dann nochmal sortieren für die txt datei
    saveEloFile(eloRanking, gameName)
    print(eloRanking)
    return eloRanking


#test = [2,3,1,4,5]
#print(sortModels(test))

#TODO sort ranking worst to best. change names of (best-)model files. (from name to temp_name to new_name) 

#TODO the whole file is a little ugly. housekeeping!




#bMap = {"synn": 1, "maij": 1}

#updatedElos = naiveElo(1.0, 2.0, 1)
#print(updatedElos)
