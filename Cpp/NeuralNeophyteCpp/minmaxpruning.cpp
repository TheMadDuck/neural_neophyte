#include "minmaxpruning.h"
#include <iostream>

MinMaxPruning::MinMaxPruning()
{
    _gameLogic = new FourInARow;
}

MinMaxPruning::~MinMaxPruning()
{
    delete _gameLogic;
}


int MinMaxPruning::exploited_mcts(Field *field, Tree *tree, std::vector<int> legalMoves, LogisticSgd classifier, std::vector<int> players, int roundNumber, int playerNumber, float randomProbability)
{
    Tree* mcts_tree;
    if (tree){
        mcts_tree = tree;
    }
    else{
        mcts_tree = new Tree();
    }
    std::cout << "legalMoves: " << legalMoves.size() << std::endl;
    for (int move: legalMoves) {
        //Field* fieldCopy = new Field(field); //needs copy constructor (rule of 5)
        Field* fieldCopy(field);
        std::cout << "teeeeeeeest0" << std::endl;
        //Field fieldCopy(field);  //Testen!!!
        std::cout << "teeeeeeeest1" << std::endl;

        GameFlow tempGameFlow(classifier, _gameLogic, fieldCopy, roundNumber);
        std::cout << "teeeeeeeest2" << std::endl;
        std::vector<int> moveVector = {move};
        std::cout << "teeeeeeeest3" << std::endl;
        std::vector<int> path = tempGameFlow.runGameFlow(players, moveVector);
        std::cout << "teeeeeeeest4" << std::endl;
        if(tempGameFlow.getWinner() == playerNumber){
            mcts_tree->addPathRec(path, 1);
        }
        else{
            mcts_tree->addPathRec(path, 0);
        }
        std::cout << "teeeeeeeest5" << std::endl;
        //delete fieldCopy;
        std::cout << "teeeeeeeest6" << std::endl;
//        delete tempGameFlow;
    }

    std::cout << "teeeeeeeest7" << std::endl;
    int gameQuantity = 8;
    for (int i = 0; i < gameQuantity; ++i) {
        //int move = 3;
        int move = mcts_tree->getNextMove();
        Field* fieldCopy(field);  //Testen!!!

        GameFlow tempGameFlow(classifier, _gameLogic, fieldCopy, roundNumber);
        std::vector<int> moveVector = {move};
        std::vector<int> path = tempGameFlow.runGameFlow(players, moveVector);
        if(tempGameFlow.getWinner() == playerNumber){
            mcts_tree->addPathRec(path, 1);
        }
        else{
            mcts_tree->addPathRec(path, 0);
        }
        //delete fieldCopy;
//        delete tempGameFlow;
    }
    //std::cout << "probas: " << std::endl;
    //std::cout << mcts_tree->getChilds() << std::endl;
    //std::cout << mcts_tree->getProbabilities() << std::endl;
    return mcts_tree->getBestMove();
}
