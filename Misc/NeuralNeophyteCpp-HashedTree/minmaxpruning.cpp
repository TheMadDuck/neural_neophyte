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


Position MinMaxPruning::exploited_mcts(Field *field, Tree *tree, LogisticSgd classifier, int roundNumber, int playerNumber, std::vector<Position> gamePath, float randomProbability, NRandomDistrib* nRd)
{
    Tree* mcts_tree;
    if (tree){
        mcts_tree = tree->lookUp(gamePath);
    }
    else{
        //mcts_tree = new Tree();
    }

    int gameQuantity = 8;
    for (int i = 0; i < gameQuantity; ++i) {
        int amountPossibleMoves = _gameLogic->getLegalInputs().size();
        int moveHash = mcts_tree->getNextMove(amountPossibleMoves, playerNumber);
        //std::cout << "moveHash: " << moveHash << std::endl;
        Position move;
        for (Position possibleMove : _gameLogic->getLegalInputs()){
            //std::cout << possibleMove.getHash(10) << std::endl;
            if(possibleMove.getHash(10) == moveHash){
                //std::cout << "hell yeaaaaaaah " << std::endl;
                move = possibleMove;
            }
        }
        Field* fieldCopy = new Field(*field);

        GameFlow tempGameFlow(classifier, _gameLogic, fieldCopy, nullptr, roundNumber, randomProbability, nRd, gamePath);
        std::vector<Position> path;
        if (moveHash != -1){
            //std::cout << "Ham - " << std::endl;
            //move.setRandomnes(false);
            //std::cout << move.getHash(10) << std::endl;
            std::vector<Position> moveVector = {move};
            path = tempGameFlow.runGameFlow({-1, -1}, moveVector);
            //std::cout << "Burger " << std::endl;
        }
        else{ // play now random
            //move.setRandomnes(true);
            path = tempGameFlow.runGameFlow({-1, -1});
        }

        if(tempGameFlow.getWinner() != 0){
            tree->addPathRec(path, tempGameFlow.getWinner());
        }
        delete fieldCopy;
    }
    int bestMoveHash = mcts_tree->getBestMove(playerNumber);
    Position move;
    for (Position possibleMove : _gameLogic->getLegalInputs()){
        if(possibleMove.getHash(10) == bestMoveHash){
            move = possibleMove;
        }
    }
    return move;
}
