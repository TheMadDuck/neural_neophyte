import numpy as np
#########################################
#import own random distrib
import nRandomDistrib.nRand as nRand

#########################################
import AIenvironment as AIEnv
import gameFlowClass as gFC

def getTrainTestValidate(gameFlow, numberTrain, numberTest, numberValidate, KI_Number):
    """
    get the winning moves of many games (KIone vs. KItwo)
    """

    #game = gFC.gameFlowClass()
    winnerPoolTrain =[[],[]]
    for i in range(numberTrain):
        if (i % 100 == 0):
            print ("trainset number: " + str(i))
        KI_One = nRand.nRand(KI_Number)
        KI_Two = nRand.nRand(KI_Number)

        #print ("KI_Number: " + str(KI_Number) + " KI_One: " + str(KI_One) + " KI_Two: " + str(KI_Two))
        #return 0
        #field, position = AIEnv.gameFlow([KI_One, KI_Two])
        gameFlow.resetgame()
        field, position = gameFlow.gameFlow([KI_One, KI_Two])
        winnerPoolTrain[0].extend(field)   #TODO append und etend checken! in der fourInARow - Class gibts auch noch so kandidaten!!
        winnerPoolTrain[1].extend(position)

    winnerPoolTest =[[],[]]
    for i in range(numberTest):
        KI_One = nRand.nRand(KI_Number)
        KI_Two = nRand.nRand(KI_Number)
        #field, position = AIEnv.gameFlow([KI_One, KI_Two])
        gameFlow.resetgame()
        field, position = gameFlow.gameFlow([KI_One, KI_Two])
        winnerPoolTest[0].extend(field)
        winnerPoolTest[1].extend(position)

    winnerPoolValidate =[[],[]]
    for i in range(numberValidate):
        KI_One = nRand.nRand(KI_Number)
        KI_Two = nRand.nRand(KI_Number)
        #field, position = AIEnv.gameFlow([KI_One, KI_Two])
        gameFlow.resetgame()
        field, position = gameFlow.gameFlow([KI_One, KI_Two])
        winnerPoolValidate[0].extend(field)
        winnerPoolValidate[1].extend(position)


    dataset = np.array((winnerPoolTrain, winnerPoolTest, winnerPoolValidate))   ## gucken wie dataset auszusehen hat, villeicht auch ([],(),[[]]....

    return dataset
