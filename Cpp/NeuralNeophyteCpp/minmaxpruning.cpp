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


int MinMaxPruning::exploited_mcts(Field *field, Tree *tree, std::vector<int> legalMoves, LogisticSgd classifier, std::vector<int> players, int roundNumber, int playerNumber, float randomProbability, NRandomDistrib* nRd)
{
    Tree* mcts_tree;
    if (tree){
        mcts_tree = tree;
    }
    else{
        //mcts_tree = new Tree();
    }

    int gameQuantity = 800;
    for (int i = 0; i < gameQuantity; ++i) {
        int amountPossibleMoves = _gameLogic->getLegalInputs().size();
        int move = mcts_tree->getNextMove(amountPossibleMoves, playerNumber);
        Field* fieldCopy = new Field(*field);


        GameFlow tempGameFlow(classifier, _gameLogic, fieldCopy, nullptr, roundNumber, 0.15, nRd);
        std::vector<int> path;
        if (move != -1){
            std::vector<int> moveVector = {move};
            path = tempGameFlow.runGameFlow({-1, -1}, moveVector);
        }
        else{ // play now random
            path = tempGameFlow.runGameFlow({-1, -1});
        }

        for (auto i:path){
            std::cout << i << " ";
        }
        std::cout << "< mcts path" << std::endl;

        if(tempGameFlow.getWinner() != 0){
            std::cout << "tempGameFlow" << tempGameFlow.getWinner() << std::endl;
            mcts_tree->addPathRec(path, tempGameFlow.getWinner());
            /*
            for(auto player: players){
                if(tempGameFlow.getWinner() ==player){
                    mcts_tree->addPathRec(path, 1, player);
                }
                else{
                    mcts_tree->addPathRec(path, 0, player);
                }
            }
            */
            /*
            if(tempGameFlow.getWinner() == playerNumber){
                mcts_tree->addPathRec(path, 1);
            }
            else{
                mcts_tree->addPathRec(path, 0);
            }
            */
        }
        delete fieldCopy;
//        delete tempGameFlow;
    }
    //std::cout << "probas: " << std::endl;
    //std::cout << mcts_tree->getChilds() << std::endl;
    //std::cout << mcts_tree->getProbabilities() << std::endl;
    //mcts_tree->getBestMove(playerNumber);

    return mcts_tree->getBestMove(playerNumber);
}
