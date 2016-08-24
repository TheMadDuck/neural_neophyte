#ifndef MODELHANDLER_H
#define MODELHANDLER_H
#include <string>
#include <iostream>
#include <sys/stat.h>
#include "learn_algorithms/cpp_based/logisticsgd.h"

class ModelHandler
{
public:
    ModelHandler();
    std::vector<std::string> folderHandler(std::string gameName);
    int loadBestModel(LogisticSgd classifier, std::string gameName); //TODO: see the todo in gameFlow.h
};

#endif // MODELHANDLER_H

