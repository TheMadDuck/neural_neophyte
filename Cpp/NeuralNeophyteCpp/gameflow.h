#ifndef GAMEFLOW_H
#define GAMEFLOW_H
#include <array>
#include <random>
#include <chrono>
#include "learn_algorithms/cpp_based/logisticsgd.h" //TODO: here and in next line realy explizit includes or just interfaces??
#include "games/fourinarow.h"
#include "field.h"
#include "tree.h"
#include "minmaxpruning.h"
#include "savelist.h"
#include "n_random_distrib/nrandomdistrib.h"

class GameFlow
{
public:
    GameFlow(LogisticSgd classifier, FourInARow *gameLogic, Field* field = nullptr, Tree* tree = new Tree(), int roundNumber = 0, int amountRandom = 0.15,  NRandomDistrib *nRd = nullptr, std::vector<int> gamePath = {});
    ~GameFlow();
    int AI_Move(int playerNumber, std::vector<int> legalMoves, std::vector<int> players, float randomMoveProba, SaveList *saveTheGame);
    int Human_Move(std::vector<int> legalMoves);
    std::vector<int> runGameFlow(std::vector<int> player, std::vector<int> prefixPath = {}, SaveList* saveList = nullptr);
    int getWinner();
    void resetGame();
    int addPrefixPath(std::vector<int> prefixPath);

    void test();
    void test2();
private:
    std::random_device seed;
//    std::mt19937 rd;

    //SaveList* saveList; // check this (realy a pointer?)
    std::vector<int> _gamePath;
    LogisticSgd _classifier;
    FourInARow *_gameLogic;
    Field *_field;
    int _roundNumber;
    float _amountRandom;
    Tree *_tree;
    int _winner;
    std::mt19937 _rd;
    NRandomDistrib* _nRd;
};

#endif // GAMEFLOW_H
