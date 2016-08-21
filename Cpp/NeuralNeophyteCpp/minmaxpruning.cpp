#include "minmaxpruning.h"

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
    for (int move: legalMoves) {
       // Field* fieldCopy = new Field(field); //needs copy constructor (rule of 5)
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
        delete fieldCopy;
//        delete tempGameFlow;
    }
    int gameQuantity = 8;
    for (int i = 0; i < gameQuantity; ++i) {
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
        delete fieldCopy;
//        delete tempGameFlow;
    }
    //std::cout << "probas: " << std::endl;
    //std::cout << mcts_tree->getChilds() << std::endl;
    //std::cout << mcts_tree->getProbabilities() << std::endl;
    return mcts_tree->getBestMove();
}
