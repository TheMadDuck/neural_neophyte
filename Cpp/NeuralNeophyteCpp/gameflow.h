#ifndef GAMEFLOW_H
#define GAMEFLOW_H
#include <array>
#include "learn_algorithms/cpp_based/logisticsgd.h" //TODO: here and in next line realy explizit includes or just interfaces??
#include "games/fourinarow.h"

class GameFlow
{
public:
    GameFlow(LogisticSgd classifier, FourInARow *gameLogic);
    void runGameFlow(std::array<int, 2> player);
};

#endif // GAMEFLOW_H
