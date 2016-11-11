#ifndef MINMAXPRUNING_H
#define MINMAXPRUNING_H

#include "field.h"
#include "tree.h"
#include "gameflow.h"
#include "games/fourinarow.h"
#include "learn_algorithms/cpp_based/logisticsgd.h"
#include "n_random_distrib/nrandomdistrib.h"

class MinMaxPruning
{
public:
    MinMaxPruning();
    ~MinMaxPruning();
    int exploited_mcts(Field *field, //TODO: field und tree wirklich pointer?
                       Tree *tree, //TODO: field und tree wirklich pointer?
                       std::vector<int> legalMoves,
                       LogisticSgd classifier,
                       std::vector<int> players,
                       int roundNumber,
                       int playerNumber,
                       std::vector<int> gamePath,
                       float randomProbability,
                       NRandomDistrib* nRd);
private:
    FourInARow* _gameLogic;
};

#endif // MINMAXPRUNING_H
