#include "minmaxpruning.h"
#include <iostream>

MinMaxPruning::MinMaxPruning()
{
    _gameLogic = new FourInARow();
}

MinMaxPruning::~MinMaxPruning()
{
    delete _gameLogic;
}


int MinMaxPruning::exploited_mcts(Field *field, Tree *tree, std::vector<int> legalMoves, LogisticSgd classifier, std::vector<int> players, int roundNumber, int playerNumber, std::vector<int> gamePath, float randomProbability, NRandomDistrib* nRd)
{
    Tree* mcts_tree;
    if (tree){
        mcts_tree = tree->lookUp(gamePath);
    }
    else{
        //mcts_tree = new Tree();
    }

    int gameQuantity = 800;
    for (int i = 0; i < gameQuantity; ++i) {
        int amountPossibleMoves = _gameLogic->getLegalInputs().size();
        int move = mcts_tree->getNextMove(amountPossibleMoves, playerNumber);
        Field* fieldCopy = new Field(*field);


        GameFlow tempGameFlow(classifier, _gameLogic, fieldCopy, nullptr, roundNumber, 0.15, nRd, gamePath);
        std::vector<int> path;
        if (move != -1){
            std::vector<int> moveVector = {move};
            path = tempGameFlow.runGameFlow({-1, -1}, moveVector);
        }
        else{ // play now random
            path = tempGameFlow.runGameFlow({-1, -1});
        }
        /*
        for (auto i:path){
            std::cout << i << " ";
        }
        std::cout << "< mcts path" << std::endl;
        */

        if(tempGameFlow.getWinner() != 0){
            tree->addPathRec(path, tempGameFlow.getWinner());
        }
        delete fieldCopy;
    }

    return mcts_tree->getBestMove(playerNumber);
}
