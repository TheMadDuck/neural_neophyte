#ifndef MENU_H
#define MENU_H
#include <string>
#include "games/fourinarow.h"
#include "learn_algorithms/cpp_based/logisticsgd.h"
#include "gameflow.h"
#include "modelhandler.h"
#include "traintestvalidate.h"
#include "eloranking.h"

class Menu
{
public:
    Menu();
private:
    int mode;
    std::string gameName;
    int numberModels;
    int humanPlayerNumber;

    FourInARow *gameLogic;
    GameFlow *gameFlow;

    ModelHandler modelHandler;
    LogisticSgd classifier;
};

#endif // MENU_H
