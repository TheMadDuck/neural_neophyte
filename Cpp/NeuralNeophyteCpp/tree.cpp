#include "tree.h"
#include <iostream>
#include <math.h>

Tree::Tree(int move, int depth, int numberWon, int numberPlayed, std::vector<Tree *> childs)
    :_move(move), _depth(depth), _numberWon(numberWon), _numberPlayed(numberPlayed), _childs(childs)
{
}

int Tree::getNumberWon()
{
    return _numberWon;
}

int Tree::getNumberPlayed()
{
    return _numberPlayed;
}

int Tree::getDepth()
{
    return _depth;
}

std::vector<Tree*> Tree::getChilds()
{
    std::vector<Tree*> childList = {};
    for(Tree* child : _childs){
        childList.push_back(child);
    }
    return childList;
}

void Tree::printTree()
{
    std::cout << "move: " << _move
              << " depth: " << _depth
              << " numberPlayed: " << _numberPlayed
              << " numberWon: " << _numberWon
              << std::endl;
//    if(_childs){
    for(Tree* child: _childs){
            child->printTree();
    }
}

std::vector<int> Tree::getPreOrder(std::vector<int> preOrderList)
{
    preOrderList.push_back(_move);
    for(Tree* child: _childs){
        child->getPreOrder(preOrderList);
    }
    return preOrderList;
}

void Tree::addPath(std::vector<int> path, int winOrLoss)
{
    _numberPlayed += 1;
    _numberWon  += winOrLoss;
    for(int move: path){
        bool pathExist = false;
        for(Tree* child: _childs){
            if (move == child->_move) {
                pathExist = true;
                child->_numberPlayed += 1;
                child->_numberWon += winOrLoss;
                //this = child;  //is this (addPath) iterativ function used?
            }
        }
        if (! pathExist) {
            Tree* newChild = new Tree();
            newChild->_move = move;
            newChild->_depth = _depth + 1;
            newChild->_numberPlayed += 1;
            newChild->_numberWon += winOrLoss;
            _childs.push_back(newChild); // in _childs should be pointers, not real objects.
            //this = newChild;
        }
    }
}

void Tree::addPathRec(std::vector<int> path, int winOrLoss)
{
    _numberPlayed += 1;
    _numberWon += winOrLoss;
    bool pathExist = false;
    if (path.empty()){ //testen
        return;
    }
    for(Tree* child: _childs){
        if (path[0] == child->_move) {
            pathExist = true;
            path.erase(path.begin()); // ACHTUNG INEFIZIENT !!!
            child->addPathRec(path, winOrLoss);
            return;
        }
    }
    if (pathExist == false) {
        Tree* newChild = new Tree();
        newChild->_move = path[0];
        newChild->_depth = _depth + 1;
        _childs.push_back(newChild);
        path.erase(path.begin());
        newChild->addPathRec(path, winOrLoss);
        return;
    }


}

int Tree::getBestMove()
{
    double win_probability = 0;
    Tree* bestMove;
    for(Tree* child: _childs){
        double win_ratio;
        if (child->_numberPlayed == 0) {
            win_ratio = 0;
        }
        else {
            win_ratio = (double)child->_numberWon / (double)child->_numberPlayed;
        }

        if (win_ratio >= win_probability) {
            win_probability = win_ratio;
            bestMove = child;
        }
        return bestMove->_move;
    }
}

int Tree::getNextMove()
{
    double next_probability = 0;
    Tree* nextMove;
    double c = sqrt(2);
    for(Tree* child: _childs){
        double next_ratio;
        if (child->_numberPlayed == 0) {
            next_ratio = 0;
        }
        else{
            next_ratio = ((double)child->_numberWon /(double)child->_numberWon) + (c * sqrt(log(_numberPlayed)/(double)child->_numberPlayed));
        }

        if (next_ratio >= next_probability) {
            next_probability = next_ratio;
            nextMove = child;
        }
    }
    return nextMove->_move;
}

std::vector<double> Tree::getProbabilities()
{
    std::vector<double> probabilities;
    int index = 0;
    for(Tree* child: _childs){
        index += 1;
        double win_ratio;
        if(child->_numberPlayed == 0){
            win_ratio = 0;
        }
        else{
            win_ratio = (double)child->_numberWon / (double)child->_numberPlayed; // use exploited algo?
        }
        probabilities.push_back(win_ratio);
    }
    return probabilities;
}

void Tree::mergeTrees(Tree)
{
    return;
}

void Tree::cutRoot(int nextRoot)
{
    for(Tree* child: _childs){
        if (child->_move == nextRoot) {
            // TODO: copy child to self!!
//            _move, _depth, _numberWon, _numberPlayed, _childs = child->_move, child->_depth, child->_numberWon, child->_numberPlayed, child->_childs; //TODO TESTEEN
            _move = child->_move;
            _depth = child->_depth;
            _numberWon = child->_numberWon;
            _numberPlayed = child->_numberPlayed;
            _childs = child->_childs;
            delete child;
        }
    }
}

bool Tree::Test()
{
    int testA = 3;
    int testB = 2;

    double testC = log(2);
    std::cout << testC << std::endl;
    std::vector<int> path = {0, 3, 14, 9, 17};
    std::vector<int> path2 = {0, 3, 66, 6, 6};
    std::vector<int> path3 = {32, 212, 15, 221, 74, 23, 0, 2};

    int win = 1;
    int loss = 0;

    Tree tree; // test as obj and test as pointer.
    tree.addPath(path, win);
    tree.addPath(path2, loss);
    tree.addPath(path3, loss);
    tree.printTree();
    std::cout << "\n \n" << "preOrder:" <<std::endl;
    auto things = tree.getPreOrder();
    for (auto thing: things ) {
        std::cout << thing << std::endl;
    }
    std::cout << std::endl;
    std::cout << "bestMove:" << std::endl;
    std::cout << tree.getBestMove() << std::endl;
    std::cout << "probabilities:" << std::endl;
    auto things2 = tree.getProbabilities();
    for (auto thing: things2 ) {
        std::cout << thing << std::endl;
    }
    std::cout << std::endl;

}


