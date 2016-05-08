import os

#########################################
#create folder for best_models
def folderHandler(gameName):
    if (not os.path.isdir("./best_models")):
        os.makedirs("./best_models") # maybe in a try catch block
        print("best models is created")

#    gameName = subPr.getName()
    if (not os.path.isdir("./best_models/" + str(gameName))):
        os.makedirs("./best_models/" + str(gameName))
        print(str(gameName) + "-folder is created")

    classifier_models = []

    """
    # ACHTUNG: reihenfolge wird so wohl nicht eingehalten:
    for file in os.listdir("./best_models/" + str(gameName)):
        if file.endswith(".pkl"):
            classifier_models.append("./best_models/" + str(gameName) + "/" + str(file))
    """

    path = "./best_models/" + str(gameName) + "/"
    number_models = len([name for name in os.listdir(path) if os.path.isfile(os.path.join(path,name)) and name.endswith('.pkl')])

    for i in range(number_models):
        classifier_models.append("./best_models/" + str(gameName) + "/best_model_" + str(i) + ".pkl")
    
    print (classifier_models)
    return classifier_models

    #TODO: add all files(filenames) in this directory to an (global) array called 'models'. 'amount of models' is also important



#########################################

def loadBestModel(classifier, gameName):
#    if(os.path.isfile("./best_model.pkl")):  #./ testen?
#    gameName = subPr.getName()
#    filePath = "./best_models/" + str(gameName) + "/best_model.pkl"

    filePaths = folderHandler(gameName)
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
