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


int MinMaxPruning::exploited_mcts(Field *field, Tree *tree, std::vector<int> legalMoves, LogisticSgd classifier, std::vector<int> players, int roundNumber, int playerNumber, float randomProbability)
{
    Tree* mcts_tree;
    if (tree){
        mcts_tree = tree;
    }
    else{
        //mcts_tree = new Tree();
    }
    /*
    for (int move: legalMoves) {                                                                 /// DELETE THIS PART. change tree.getNextMove() so that if a move has _numberPlayed=0 it gets played! or not?
        //Field* fieldCopy = new Field(field); //needs copy constructor (rule of 5)
        //Field* fieldCopy(field);
        Field* fieldCopy = new Field(*field);
        //Field fieldCopy(field);  //Testen!!!

        //GameFlow tempGameFlow(classifier, _gameLogic, fieldCopy, roundNumber, randomProbability, mcts_tree); // tree weiter vererben???
        GameFlow tempGameFlow(classifier, _gameLogic, fieldCopy, nullptr, roundNumber);
        std::vector<int> moveVector = {move};
        std::vector<int> path = tempGameFlow.runGameFlow(players, moveVector);
        if(tempGameFlow.getWinner() == playerNumber){
            mcts_tree->addPathRec(path, 1);
        }
        else{
            mcts_tree->addPathRec(path, 0);
        }
        delete fieldCopy;
//        delete tempGameFlow;
    }
    */

    int gameQuantity = 8;
    for (int i = 0; i < gameQuantity; ++i) {
//        if(tree->_childs.size() < _gameLogic->getLegalInputs().size())
        int amountPossibleMoves = _gameLogic->getLegalInputs().size();
        int move = mcts_tree->getNextMove(amountPossibleMoves);
        std::cout << "my move: " <<  move << std::endl;
        //Field* fieldCopy(field);  //Testen!!!
        Field* fieldCopy = new Field(*field);


        GameFlow tempGameFlow(classifier, _gameLogic, fieldCopy, nullptr, roundNumber);
        std::vector<int> path;
        if (move != -1){
            std::vector<int> moveVector = {move};
            path = tempGameFlow.runGameFlow(players, moveVector);
        }
        else{ // play now random
            path = tempGameFlow.runGameFlow({-1, -1});
        }
        std::cout << "getWinnter: " << tempGameFlow.getWinner() << std::endl;
        if(tempGameFlow.getWinner() == playerNumber){
            mcts_tree->addPathRec(path, 1);
        }
        else{
            mcts_tree->addPathRec(path, 0);
        }
        delete fieldCopy;
//        delete tempGameFlow;
    }
    //std::cout << "probas: " << std::endl;
    //std::cout << mcts_tree->getChilds() << std::endl;
    //std::cout << mcts_tree->getProbabilities() << std::endl;
    return mcts_tree->getBestMove();
}
