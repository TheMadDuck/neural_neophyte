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

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>

class PlayerInformation; //forward declaration
class Player
{
public:
    Player();
    Player(std::vector<int> models, int roundNumber = 0); // vector of scroes?
    void setScore(std::vector<double> score);
    void addPlayer(int model); // necessary?
    void setActivePlayerByRoundNumber(int roundNumber);  //better name?
    void changePlayer(int number, int model);
    int getWinnerNumber();
    double getWinnerScore();
    void endGame(std::vector<double> score = {});
    bool isOver();
    int amountPlayer();
    //int getPlayerModel(int playerNumber);
    //double getPlayerScore(int playerNumber);
    PlayerInformation getActivePlayer();
    int getActivePlayerNumber();
    int getActiveModel();
    double getActiveScore();
    bool onlyComputerPlayer();
    void nextPlayer();
    void resetGame();
private:
    std::vector<PlayerInformation> _players;
    int _amountPlayers;
    int _activePlayer;
    bool _onlyComputerPlayer;
    bool _gameOver;
    bool _draw;   // not used at the moment
    PlayerInformation* _winner = nullptr;
};

class PlayerInformation
{
    friend class Player;
public:
    PlayerInformation();
private:
    int _playerNumber;
    int _playerModel;
    double _playerScore;  //rename in _playerFitnes?
    bool _removed;
    // team
    // internal information (e.g. card information in poker)
    // % of random moves (mistakes)
    // ...
};

#endif // PLAYER_H
