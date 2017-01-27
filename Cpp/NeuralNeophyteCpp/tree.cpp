/*   Copyright (C) 2016 by Daniel M.H. Noll                                *
 *   Author: Daniel Noll                                                   *
 *                                                                         *
 *   Email: sport.mann@gmx.de                                              *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * Redistribution and use in source and binary forms, with or without      *
 * modification, are permitted provided that the following conditions are  *
 *  met:                                                                   *
 *                                                                         *
 *     * Redistributions of source code must retain the above copyright    *
 *       notice, this list of conditions and the following disclaimer.     *
 *     * Redistributions in binary form must reproduce the above copyright *
 *       notice, this list of conditions and the following disclaimer in   *
 *       the documentation and/or other materials provided with            *
 *       the distribution.                                                 *
 *     * Neither the name of the author nor the names of its contributors  *
 *       may be used to endorse or promote products derived from this      *
 *       software without specific prior written permission.               *
 *                                                                         *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 ***************************************************************************/

#include "tree.h"
#include <iostream>
#include <math.h>

/*
Tree::Tree()
{
    _move = -1, _depth = 0, _numberWon = 0, _numberPlayed = 0, _childs = {};
}
*/

Tree::Tree(int amountPlayer, int depth, std::vector<double> numberWon, int numberPlayed, std::vector<Tree *> childs)
    :_amountPlayer(amountPlayer), _depth(depth), _numberWon(numberWon), _numberPlayed(numberPlayed), _childs(childs)
{
    for(int i = 0; i < amountPlayer; ++i){
       _numberWon.push_back(0);  // why?
    }
}


Tree::~Tree()
{
    //    delete _childs;
    //deleteTree(this);
}

Tree::Tree(const Tree &other)
{
    std::cout << "tree constr. 2" << std::endl;
    _move = other._move;
    _depth = other._depth;
    _numberWon = other._numberWon;
    _numberPlayed = other._numberPlayed;
    _childs = other._childs;
}

Tree::Tree(Tree &&other)
    :_move(other._move), _depth(other._depth), _numberWon(other._numberWon), _numberPlayed(other._numberPlayed), _childs(other._childs)
{
    std::cout << "tree constr. 3" << std::endl;
}

Tree &Tree::operator=(const Tree &other)
{
    std::cout << "tree constr. 4" << std::endl;
    _move = other._move;
    _depth = other._depth;
    _numberWon = other._numberWon;
    _numberPlayed = other._numberPlayed;
    _childs = other._childs;
    return *this;
}

Tree &Tree::operator=(Tree &&other)
{
    std::cout << "tree constr. 5" << std::endl;
    _move = other._move;
    _depth = other._depth;
    _numberWon = other._numberWon;
    _numberPlayed = other._numberPlayed;
    _childs = other._childs;
    return *this;
}

double Tree::getNumberWon(int player)
{
    return _numberWon[player ];
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
    std::cout << "move: " << _move[0]  // TODO: print whole vector!
              << " depth: " << _depth
              << " numberPlayed: " << _numberPlayed;
    for (auto i : _numberWon){
        std::cout << " numberWon: " << i;
    }
    std::cout << std::endl;
    for(Tree* child: _childs){
            child->printTree();
    }
}

std::vector<Position> Tree::getPreOrder(std::vector<Position> preOrderList)
{
    std::cout << "does not work yet" << std::endl;
    preOrderList.push_back(_move);
    if(!_childs.empty()){
    for(Tree* child: _childs){
        child->getPreOrder(preOrderList);
    }}
    return preOrderList;
}
/*
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
*/
void Tree::addPathRec(std::vector<Position> path, int winner, double score)
{
    _numberPlayed += 1;
    _numberWon[winner] += score;

    if (path.empty()){
        return;
    }

    for(Tree* child: _childs){
        if (path[0] == child->_move) {
            path.erase(path.begin()); // ACHTUNG INEFIZIENT !!!
            child->addPathRec(path, winner);
            return;
        }
    }
    Tree* newChild = new Tree(_amountPlayer);
    newChild->_move = path[0];
    newChild->_depth = _depth + 1;
    _childs.push_back(newChild);
    path.erase(path.begin());
    newChild->addPathRec(path, winner);

    return;
}

Position Tree::getBestMove(int player)
{
    double win_probability = 0;
    Position bestMove;
    for(Tree* child: _childs){
        double win_ratio;
        if (child->_numberPlayed == 0) { // TODO: design as in getNextMove() /also the setRandom()
            win_ratio = 0;
        }
        else {
            win_ratio = (double)child->_numberWon[player] / (double)child->_numberPlayed;
        }

        if (win_ratio >= win_probability) {
            win_probability = win_ratio;
            bestMove = child->_move;
        }
    }
    return bestMove;
}

Position Tree::getNextMove(int amountPosslibleMoves, int player)
{
    double next_probability = 0;
    Position nextMove;
    double c = sqrt(2);
    for(Tree* child: _childs){
        double next_ratio;

        //TODO what to do if the game reaches a draw?
        if (amountPosslibleMoves > _childs.size()){  // return -1 for random move
            nextMove.setRandomnes(true);
            return nextMove;
        }
        else{
            next_ratio = ((double)child->_numberWon[player] /(double)child->_numberPlayed) + (c * (double)sqrt((double)log(_numberPlayed)/(double)child->_numberPlayed));
            nextMove.setRandomnes(false);
            //std::cout << "Win-Probability: " << next_ratio << " - move: " << child->_move << std::endl;
        }

        if (next_ratio >= next_probability) {
            next_probability = next_ratio;
            nextMove = child->_move;
        }
    }
    return nextMove;
}

std::vector<double> Tree::getProbabilities(int player)
{
    std::vector<double> probabilities;
    for(Tree* child: _childs){
        double win_ratio = 0;
        if(child->_numberPlayed != 0){
            win_ratio = (double)child->_numberWon[player] / (double)child->_numberPlayed;
        }

        probabilities.push_back(win_ratio);

    }
    for(double i: probabilities){
        std::cout << " i:" << i << std::endl;
    }
    return probabilities;
}

void Tree::mergeTrees(Tree)
{
    std::cout << "not yet implemented" << std::endl;
    return;
}

void Tree::cutRoot(Position nextRoot)
{
    for(Tree* child: _childs){
        if (child->_move == nextRoot) {
            _move = child->_move;
            _depth = child->_depth;
            _numberWon = child->_numberWon;
            _numberPlayed = child->_numberPlayed;
            _childs = child->_childs;
            delete child;
        }
    }
}

Tree* Tree::lookUp(std::vector<Position> path)
{
    Tree* parent = this;
    for(Position subTree: path){
        for(Tree* child: parent->_childs){
            if (child->_move == subTree){
                parent = child;
            }
        }
    }
    return parent;
}

void Tree::deleteTree(Tree *tree)
{
    /*if (tree->getChilds().size() == 0){
        std::cout << "yo";
        delete tree;
        return;
    }
    */
    for(Tree* child: tree->getChilds()){
        deleteTree(child);
    }
    delete tree;
    return;
}

bool Tree::Test()
{
    bool testV = true;

    std::vector<int> path = {0, 3, 14, 9, 17};
    std::vector<int> path2 = {0, 3, 66, 6, 6};
    std::vector<int> path3 = {32, 212, 15, 221, 74, 23, 0, 2};

    int player1 = 1;
    int player2 = 2;

    Tree* tree = new Tree(2); // test as obj and test as pointer.
    /*tree->addPathRec(path, player2);
    tree->addPathRec(path2, player1);
    tree->addPathRec(path3, player2);
    */
    tree->printTree();
    /*std::cout << "\n \n" << "preOrder:" <<std::endl;
    auto things = tree.getPreOrder();
    for (auto thing: things ) {
        std::cout << thing << std::endl;
    }*/
    /*
    Tree* tempTree = tree->lookUp({0, 3});
    std::cout << "tempTree best Move: " << tempTree->getBestMove(2) << std::endl;
    std::cout <<"getNext1: " << tempTree->getNextMove(0, 1) << std::endl;
    std::cout <<"getNext2: " << tempTree->getNextMove(0, 2) << std::endl;
    if (getBestMove(1) != 32){
        testV = false;
    }
    */
    std::cout << "probabilities:" << std::endl;
    auto things2 = tree->getProbabilities(1);
    for (auto thing: things2 ) {
        std::cout << thing << std::endl;
    }
    return testV;

}


