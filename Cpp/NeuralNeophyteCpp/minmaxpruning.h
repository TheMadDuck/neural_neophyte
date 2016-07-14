#ifndef MINMAXPRUNING_H
#define MINMAXPRUNING_H

#include "field.h"
#include "tree.h"
#include "learn_algorithms/cpp_based/logisticsgd.h"

class MinMaxPruning
{
public:
    MinMaxPruning();
    int exploited_mcts(Field *field, //TODO: field und tree wirklich pointer?
                       Tree *tree, //TODO: field und tree wirklich pointer?
                       std::vector<int> legalMoves,
                       LogisticSgd classifier,
                       std::vector<int> players,
                       int roundNumber,
                       int playerNumber,
                       float randomProbability);
};

#endif // MINMAXPRUNING_H
