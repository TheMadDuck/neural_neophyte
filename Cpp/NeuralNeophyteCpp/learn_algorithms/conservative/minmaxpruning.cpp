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
#include "../../games/fourinarow.h"  // todo remove include here
#include "../../games/chess.h" // todo remove include here
#include "../../games/pegsolitaire.h"

MinMaxPruning::MinMaxPruning(std::string gameName)  // todo if the argument is not the game-name but the GameLogic itself: here a copy should be made with all the (game-)internal information(or without??)
{
    if(gameName == "four_in_a_row"){
        _gameLogic = new FourInARow();
    }
    if(gameName == "chess"){
        _gameLogic = new Chess();
    }
    if(gameName == "peg_solitaire"){
        _gameLogic = new PegSolitaire();
    }
}

MinMaxPruning::~MinMaxPruning()
{
    delete _gameLogic;
}


Position MinMaxPruning::exploited_mcts(Field *field, Tree *tree, Classifier *classifier, int roundNumber, int playerNumber, std::vector<Position> gamePath, float randomProbability, NRandomDistrib* nRd, int amountPossibleMoves)
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
        //int amountPossibleMoves = _gameLogic->getLegalInputs().size();
        Position move = mcts_tree->getNextMove(amountPossibleMoves, playerNumber);
        Field* fieldCopy = new Field(*field);
        GameFlow tempGameFlow(classifier, _gameLogic, fieldCopy, nullptr, roundNumber, randomProbability, nRd, gamePath);
        std::vector<Position> path;
        Player *player = new Player();
        for(int i = 0; i < _gameLogic->numberPlayers(); ++i){
            player->addPlayer(-1);
        }
        player->setActivePlayerByRoundNumber(roundNumber);
        if (!move.isRandom()){
            std::vector<Position> moveVector = {move};
            path = tempGameFlow.runGameFlow(player, moveVector);
        }
        else{ // play now random
            path = tempGameFlow.runGameFlow(player);
        }

        if(tempGameFlow.getWinner() != -1){
            tree->addPathRec(path, player->getWinnerNumber(), player->getWinnerScore()); // get winner and score from player or from tempGameFlor?
        }
        delete fieldCopy;
    }
    return mcts_tree->getBestMove(playerNumber);
}
