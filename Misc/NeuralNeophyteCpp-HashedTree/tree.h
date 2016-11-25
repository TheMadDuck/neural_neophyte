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

#ifndef TREE_H
#define TREE_H
#include <vector>
#include "data_types/position.h"

class Tree
{
public:
    Tree(int depth = 0, int numberWon = 0, int numberPlayed = 0, std::vector<Tree*> childs = {}); //TODO move als -1 initialisieren?
    ~Tree(); //destructor
    Tree(const Tree &other); //copy constructor
    Tree(Tree&& other); //move constructor
    Tree& operator=(const Tree& other); //copy assignment
    Tree& operator=(Tree&& other); //move assignment

    int getNumberWon(int player);
    int getNumberPlayed();
    int getDepth();
    std::vector<Tree *> getChilds();
    void printTree();
    std::vector<int> getPreOrder(std::vector<int> preOrderList = {});
    //void addPath(std::vector<int> path, int winOrLoss);
    void addPathRec(std::vector<Position> path, int winner);
    int getBestMove(int player);
    int getNextMove(int amountPosslibleMoves, int player);
    std::vector<double> getProbabilities(int player);
    void mergeTrees(Tree);
    void cutRoot(int nextRoot);
    Tree *lookUp(std::vector<Position> path);
    void deleteTree(Tree *tree);

    bool Test();

private:
    int _move = -1;// = -1;
    int _depth = 0;
    std::vector<int> _numberWon = {0, 0}; // todo: make alloc dynamic.
    int _numberPlayed = 0;
    std::vector<Tree*> _childs = {};
};

#endif // TREE_H
