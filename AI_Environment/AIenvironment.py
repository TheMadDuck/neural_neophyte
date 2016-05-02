'''
The AI environment. This file provides the game functionality for the neural network. It loads the necessary game functions and provides the gamefield + all game information to the net. You could say that it is the link between the game and the AI.

'''

import numpy as np
import random as rd
import pickle
import os.path
import copy

########################################
#load classifier:
import learn_algorithms.theano_based.logistic_sgd as classifier


#########################################
#load game:

import games.fourInARow as subPr

#########################################

#best_models = None

#########################################
#create folder for best_models
def folderHandler():
    if (not os.path.isdir("./best_models")):
        os.makedirs("./best_models") # maybe in a try catch block
        print("best models is created")

    gameName = subPr.getName()
    if (not os.path.isdir("./best_models/" + str(gameName))):
        os.makedirs("./best_models/" + str(gameName))
        print(str(gameName) + "-folder is created")

    classifier_models = []
    for file in os.listdir("./best_models/" + str(gameName)):
        if file.endswith(".pkl"):
            classifier_models.append("./best_models/" + str(gameName) + "/" + str(file))
    
    print (classifier_models)
    return classifier_models

    #TODO: add all files(filenames) in this directory to an (global) array called 'models'. 'amount of models' is also important



#########################################

def loadBestModel():
#    if(os.path.isfile("./best_model.pkl")):  #./ testen?
#    gameName = subPr.getName()
#    filePath = "./best_models/" + str(gameName) + "/best_model.pkl"

    filePaths = folderHandler()
    if (filePaths):
        print("best model is there")
        for i in filePaths:
            classifier.loadBestModel(i)
        return len(filePaths)
    else:
        return 0

    """
    #filePath = classifier_models[0]
    if(os.path.isfile(filePath)): #Testen!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        print("best model is there")
        classifier.loadBestModel(filePath)
        return True
    else:
        return False
    """


#########################################
# naive AI:
def AI_Move(field, playerNumber, legalMoves, bestModelExist, randomMoveProba):
    # sometimes you want a random move:
    if (rd.random() < randomMoveProba): 
        bestModelExist = 0

    if(bestModelExist):
        #TODO WICHTIG:  field glätten und in flatfield speichern

        #fieldCopy = copy.deepcopy(field)

        #print("A I")
        flatField = field.flatten()        
        flatField = np.append(flatField, playerNumber)
        return classifier.predict(flatField, bestModelExist-1)[0]
    else:
        #print("random")
        return rd.choice(legalMoves)
#########################################

#similar the human move:
def Human_Move(legalMoves):
    move = int(input("wich move do you want to make? [" + str(legalMoves) + " ]"))
    return move


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

def savePositions(field, color, position, saveList, transponiert):

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
            saveList[0][0].append(flatField)
            saveList[0][1].append(position)
            return saveList
        else:
            flatField = fieldCopy.flatten()     # Achtung: flattne macht deepcopy. für ne einfache reference benutze ravel()... <- testen
            flatField = np.append(flatField, 2)
            saveList[1][0].append(flatField)
            saveList[1][1].append(position)
            return saveList





#########################################
# virtual game flow:

def gameFlow(bestModelExist, againstHuman, humanPlayerNumber):   #TODO vieleicht eher sowas wie gameFlow(player1, player2) human:0 ai models:1-x [allerdings sollten die models extern geladen werden...)

    amountRandom = 0.2  # vieleicht ausserhalb definieren?
    legalInputs = subPr.getLegalInputs()
    if subPr.getSignal() != "legalInputs_initialized":
        print("ERROR: legal Inputs could not get initialized")

    saveList = initSaveList(False)

    field = subPr.initField()
    if subPr.getSignal() != "field_initialized":
        print("ERROR: Field could not get initialized")

    #game = subPr.gameLoop()
    roundNumber = 0
    while((subPr.getSignal() != "weHaveAWinner") or (subPr.getSignal() != "gameIsOver")):
        roundNumber += 1
        if roundNumber % 2 == 1:
            playerNumber = 1
        else:
            playerNumber = 2

        if (againstHuman): # do we play against a human?
            if (humanPlayerNumber == playerNumber): # is the human player 1 or player 2?
                position = Human_Move(legalInputs)
            else:
                position = AI_Move(field, playerNumber, legalInputs, bestModelExist, amountRandom) # get new position from extern
        else:
            position = AI_Move(field, playerNumber, legalInputs, bestModelExist, amountRandom) # get new position from extern
        subPr.isLegalMove(field, playerNumber, position)
        #print(position)
        while (subPr.getSignal() == "unvalidPlayer") or (subPr.getSignal() == "unvalidPosition" or subPr.getSignal() == "columnIsFull"):
            if (againstHuman): # do we play against a human?
                if (humanPlayerNumber == playerNumber): # is the human player 1 or player 2?
                    print("this move is not legal, please try again!!")
                    position = Human_Move(legalInputs)
                else:
                    print("ERROR: The AI-Environment could not make a legal move. will try random move..")
                    position = AI_Move(field, playerNumber, legalInputs, False, amountRandom) # get new position from extern
            else:
                print("ERROR: The AI-Environment could not make a legal move. will try random move..")
                position = AI_Move(field, playerNumber, legalInputs, False, amountRandom) # get new position from extern
            subPr.isLegalMove(field, playerNumber, position)


            '''
            if subPr.getSignal() != "moveIsLegal":
                print("ERROR: The AI-Environment could not make a legal move. will try random move..")
                position = AI_Move(field, playerNumber, legalInputs, False) 
                subPr.isLegalMove(field, playerNumber, position)
            else:
                print("yeehaaaaaaaaa")
            '''            
        saveList = savePositions(field, playerNumber, position, saveList, False)   #TODO : information wer gerade am zug ist abspeichern und providen. entweder jedes mal field invertieren oder ein feature mehr reintun.!!! 
        #TODO komplette savelist logic in die classe hier?!

        subPr.setStone(field, playerNumber, position)
        if subPr.getSignal() != "stoneIsSet":
            print("ERROR: Stone is not saved")
        if(againstHuman):
            print(" ")
            print(field)        # show field in a game vs. a human !!!
        winner = subPr.hasAWinner(field, playerNumber, position)
        if (subPr.getSignal() == "weHaveAWinner"):
            #print("we have a winner!!!")
            if winner == 0:
                print("ERROR: we could not determine who won!")
            if (againstHuman):
                print(" ")
                print("the winner is: " + str(winner))
                print(" ")
            break
        
        subPr.gameStopped(field, roundNumber)
        if (subPr.getSignal() == "gameIsOver"):
            break

#    print("################################")
#    print("spielverlauf vom Sieger (zum lernen):")
#    print(saveList[winner-1])
    
    return saveList[winner-1]

# change name (AI_environment.py)
#TODO add documentation!!!
#TODO integrate the MLP. 
#TODO human vs Ai mode basteln. (hier oder extern?)
#TODO always keep the X-best Models [X = 5 or ?], so AI-Move can choose from a set of models. <- git exclude one folder with models???!!!!!!!!
#     mayby rank those with an elo number?! 
#TODO Elo tunier. (count when an older modelling beat an younger?) higher elo -> higher probability to play! Which model plays against which model in train phase? train phase trough turnier?
#TODO enjoy life


def getTrainTestValidate(numberTrain, numberTest, numberValidate, KI_Number):
    """
    get the winning moves of many games (KIone vs. KItwo)
    """
    #classifier_models = folderHandler()
    #bestModelExist = loadBestModel()

    winnerPoolTrain =[[],[]]
    for i in range(numberTrain):
        if (i % 100 == 0):
            print ("trainset number: " + str(i))
        field, position = gameFlow(KI_Number, False, 0)
        winnerPoolTrain[0].extend(field)   #TODO append und etend checken! in der fourInARow - Class gibts auch noch so kandidaten!!
        winnerPoolTrain[1].extend(position)

    winnerPoolTest =[[],[]]
    for i in range(numberTest):
        field, position = gameFlow(KI_Number, False, 0)
        winnerPoolTest[0].extend(field)
        winnerPoolTest[1].extend(position)

    winnerPoolValidate =[[],[]]
    for i in range(numberValidate):
        field, position = gameFlow(KI_Number, False, 0)
        winnerPoolValidate[0].extend(field)
        winnerPoolValidate[1].extend(position)


    dataset = np.array((winnerPoolTrain, winnerPoolTest, winnerPoolValidate))   ## gucken wie dataset auszusehen hat, villeicht auch ([],(),[[]]....

    #TODO wirklich pickln?
#    newFile= open("gameTTV.p", "w+")
#    pickle.dump(dataset, open("gameTTV.p", "rb"))
    return dataset

############################################


"""
print("gameTTV[0][0] : ")
print (len(gameTTV[0][0]))
print("gameTTV[0][1] : ")
print (len(gameTTV[0][1]))

print("gameTTV[0][0][23]")
print(gameTTV[0][0][23])
"""

def main():
    print("Play a Game  (press 1)")
    print("Train the AI (press 2)")
    mode = int(input(""))
    while (mode != 1 and mode != 2):
        mode = int(input("press 1 or 2 !!"))
    numberModels = loadBestModel()
    if mode == 1:
        print ("do you want to be player 1 or player 2?")
        humanPlayerNumber = int(input("press 1 or 2: "))
        while (humanPlayerNumber != 1 and humanPlayerNumber != 2):
            humanPlayerNumber = int(input("press 1 or 2: "))
        
#        classifier_models = folderHandler()
        gameFlow(numberModels, True, humanPlayerNumber)  #nur gegen bestes Model !
        
    if mode == 2:
        gameTTV = getTrainTestValidate(4000,100,100, numberModels) #nur gegen bestes model?
        gameName = subPr.getName()
        #bestModelPath = "./best_models/" + str(gameName) + "/best_model.pkl"
        bestModelPath = "./best_models/" + str(gameName) + "/best_model_" + str(numberModels) + ".pkl"
        classifier.sgd_optimization(learning_rate=0.13, n_epochs=1000, dataset=gameTTV, batch_size=600, bestModelPath=bestModelPath)


main()

#folderHandler()



###########################################



'''
# more possible signals:
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




