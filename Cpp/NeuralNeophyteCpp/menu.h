#ifndef MENU_H
#define MENU_H
#include <string>
#include "games/fourinarow.h"
#include "learn_algorithms/cpp_based/logisticsgd.h"
#include "gameflow.h"
#include "modelhandler.h"
#include "traintestvalidate.h"
#include "eloranking.h"
#include "n_random_distrib/nrandomdistrib.h"

class Menu
{
public:
    Menu();
private:
    int _mode;
    std::string _gameName;
    int _numberModels;
    int _humanPlayerNumber;

    FourInARow *_gameLogic;
    GameFlow *_gameFlow;

    ModelHandler _modelHandler; //pointer?
    LogisticSgd _classifier; //pointer?
};

#endif // MENU_H
