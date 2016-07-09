#ifndef MENU_H
#define MENU_H
#include <string>
#include "games/fourinarow.h"
#include "gameflow.h"
#include "modelhandler.h"

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
};

#endif // MENU_H
