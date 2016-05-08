import AIenvironment as AIEnv

########################################
#to load the models
import modelHandler

########################################
#to eval classifiers
import eloRanking

########################################
#load classifier:
import learn_algorithms.theano_based.logistic_sgd as classifier
#import learn_algorithms.theano_based.mlp as classifier

#########################################
#load game:
import games.fourInARow as subPr


#########################################
#########################################

def main():
    AIEnv.setImports(classifier, subPr)
    print("Play a Game  (press 1)")
    print("Train the AI (press 2)")
    print("Sort existing classifiers and rank them (press 3)")
    mode = int(input(""))
    while (mode != 1 and mode != 2 and mode != 3):
        mode = int(input("press 1, 2 or 3 !!"))
    numberModels = modelHandler.loadBestModel(classifier, subPr.getName())
    gameName = subPr.getName()
    
    if mode == 1:
        print ("do you want to be player 1 or player 2?")
        humanPlayerNumber = int(input("press 1 or 2: "))
        while (humanPlayerNumber != 1 and humanPlayerNumber != 2):
            humanPlayerNumber = int(input("press 1 or 2: "))
        
#        classifier_models = folderHandler()
        if (humanPlayerNumber == 1):
            AIEnv.gameFlow([-1, numberModels])
        else:
            AIEnv.gameFlow([numberModels, -1])
        
    if mode == 2:
        gameTTV = AIEnv.getTrainTestValidate(4000,100,100, numberModels) #nur gegen bestes model?
        bestModelPath = "./best_models/" + str(gameName) + "/best_model_" + str(numberModels) + ".pkl"
        classifier.fit(learning_rate=0.13, n_epochs=1000, dataset=gameTTV, batch_size=600, bestModelPath=bestModelPath)
    
    if mode == 3:
        print("how many games should be played?")
        amountGames = int (input(""))
        eloRanking.turnier(amountGames, numberModels, gameName)
        

main()
