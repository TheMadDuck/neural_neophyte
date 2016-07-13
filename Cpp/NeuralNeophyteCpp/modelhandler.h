#ifndef MODELHANDLER_H
#define MODELHANDLER_H
#include <string>
#include "learn_algorithms/cpp_based/logisticsgd.h"

class ModelHandler
{
public:
    ModelHandler();
    int loadBestModel(LogisticSgd classifier, std::string gameName); //TODO: see the todo in gameFlow.h
};

#endif // MODELHANDLER_H

