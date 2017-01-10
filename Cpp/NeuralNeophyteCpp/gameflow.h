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

#ifndef GAMEFLOW_H
#define GAMEFLOW_H
#include <array>
#include <random>
#include <chrono>
//#include <algorithm>
#include "learn_algorithms/nn_based/design_1/logisticsgd.h" //TODO: here and in next line realy explizit includes or just interfaces??
//#include "games/fourinarow.h"
#include "games/game.h"
#include "data_types/field.h"
#include "data_types/player.h"
#include "tree.h"
#include "learn_algorithms/conservative/minmaxpruning.h"
#include "data_types/savelist.h"
#include "n_random_distrib/nrandomdistrib.h"
#include "data_types/position.h"

class GameFlow
{
public:
    GameFlow(LogisticSgd classifier, Game *gameLogic, Field* field = nullptr, Tree* tree = new Tree(), int roundNumber = 0, int amountRandom = 0.15,  NRandomDistrib *nRd = nullptr, std::vector<Position> gamePath = {});
    ~GameFlow();
    void move();
    void AI_Move();
    void Human_Move();
    std::vector<Position> runGameFlow(std::vector<int> players, std::vector<Position> prefixPath = {}, SaveList* saveList = nullptr);
    int getWinner();
    void resetGame();
    int addPrefixPath(std::vector<Position> prefixPath);

    void test();
    void test2();
private:
    std::random_device seed;

    //SaveList* saveList; // check this (realy a pointer?)
    std::vector<Position> _gamePath;
    LogisticSgd _classifier;
    //FourInARow *_gameLogic;
    Game *_gameLogic;
    Field *_field;
    int _roundNumber;
    float _amountRandom;
    Tree *_tree;
    int _winner;
    std::mt19937 _rd;
    NRandomDistrib* _nRd;
    Position _nextPosition;
    std::vector<int> _players;
    std::vector<Position> _legalMoves;
    int _playerNumber;
    Player player;
};

#endif // GAMEFLOW_H
