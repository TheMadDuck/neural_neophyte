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

#include "player.h"

Player::Player(int roundNumber)
{
    _amountPlayers = 0;
    _onlyComputerPlayer = true; // same definitions in Player(std::vector)
    _activePlayer = 0;
   // std::cout << "was geht 00" << std::endl;
   // _activePlayer = roundNumber % _amountPlayers;
   // std::cout << "was geht 01" << std::endl;
}

Player::Player(std::vector<int> models, int roundNumber)
{
    _amountPlayers = 0;
//    _activePlayer = 0;
    _onlyComputerPlayer = true;
    //int index = 1;                 // start counting at 0 or 1 ( see nextPlayer() function)
    for(int model : models){
        PlayerInformation player;  // pointer??
        player._playerModel = model;
        player._playerNumber = _amountPlayers;
        //index += 1;
        _players.push_back(player);
        _amountPlayers += 1;
        if(model == 0){
            _onlyComputerPlayer = false;
        }
    }
    _activePlayer = roundNumber % _amountPlayers;
}

void Player::addPlayer(int model)
{
    if(model == 0){
        _onlyComputerPlayer = false;
    }
    PlayerInformation player;
    player._playerModel = model;
    player._playerNumber = _amountPlayers; // if we count players at 0 then this line one up!
    _players.push_back(player);
    _amountPlayers += 1;
}

void Player::changePlayer(int number, int model)
{
    if(model == 0){
        _onlyComputerPlayer = false;
    }
    PlayerInformation player;
    player._playerModel = model;
    player._playerNumber = number;
    _players[number] = player;
}

bool Player::isOver()
{
    std::cout << "not yet implemented" << std::endl;
}

int Player::amountPlayer()
{
    return _amountPlayers;
}

PlayerInformation Player::getActivePlayer()
{
    return _players[_activePlayer];
}

int Player::getActivePlayerNumber()
{
    return _players[_activePlayer]._playerNumber;
}

int Player::getActiveModel()
{
    return _players[_activePlayer]._playerModel;
}

double Player::getActiveScore()
{
    return _players[_activePlayer]._playerScore;
}

bool Player::onlyComputerPlayer()
{
    return _onlyComputerPlayer;
}

void Player::nextPlayer()
{
    _activePlayer+=1;
    if (_activePlayer >= _amountPlayers){  // start counting at 0 or 1 ???
        _activePlayer = 0;
    }
}

void Player::resetGame()
{
    _activePlayer = 0;
}


////////////////////////////////////////////////////////
/// \brief PlayerInformation::PlayerInformation
///

PlayerInformation::PlayerInformation()
{
    _playerScore = 0;  // add _playerNumber and score?
    _removed = false;
}
