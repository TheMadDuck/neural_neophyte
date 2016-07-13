#ifndef ELORANKING_H
#define ELORANKING_H

#include "gameflow.h"

class EloRanking
{
public:
    EloRanking();
    void turnier(GameFlow *gameFlow, int amountGames, int numberModels, std::string gameName);
};

#endif // ELORANKING_H
