#include "modelhandler.h"

ModelHandler::ModelHandler()
{
}

std::vector<std::string> ModelHandler::folderHandler(std::string gameName)
{
    //if(!)
}

int ModelHandler::loadBestModel(LogisticSgd classifier, std::string gameName)
{
    std::vector<std::string> filePaths = folderHandler(gameName);
    if(filePaths.size() != 0){  // TESTEN!
        std::cout << "best model exist" << std::endl;
        for(auto path: filePaths){
            //classifier.loadBestModel(path);
        }
        return filePaths.size(); //???
    }
    else{
        return 0;
    }
}
