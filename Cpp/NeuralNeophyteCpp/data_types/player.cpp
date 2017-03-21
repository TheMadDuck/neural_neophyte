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
#include <assert.h>

/*
 * Handels the information about the player (KI-Model, playersNumber, players internal
 * information (cards in his hand etc). Also the class returns who is active in the moment
 */
Player::Player()
{
    _gameOver = false;
    _amountPlayers = 0;
    _draw = false;
    _onlyComputerPlayer = true; // same definitions in Player(std::vector)
    _activePlayer = 0;
    //_activePlayer = roundNumber % _amountPlayers;
}

Player::Player(std::vector<int> models, int roundNumber)
{
    _gameOver = false;
    _amountPlayers = 0;
    _draw = false;
    _onlyComputerPlayer = true;
    for(int model : models){
        PlayerInformation player;  // pointer??
        player._playerModel = model;
        player._playerNumber = _amountPlayers;
        player._playerScore = 0;
        _players.push_back(player);
        _amountPlayers += 1;
        if(model == 0){
            _onlyComputerPlayer = false;
        }
    }
    _activePlayer = roundNumber % _amountPlayers;
}

void Player::setScore(std::vector<double> score)
{	/*
    //std::cout << "score.size(): " << score.size() << " _player.size(): " << _players.size() << std::endl;
    if(score.size() != _players.size()){
        std::cout << "ERROR ERROR ERROR !!!" << std::endl;
    }
    // make a playerScore list in Player(not PlayerInformation). so this function has only to replace that score-vector!!!
    int index = 0;
    for(double playerScore : score){
        _players[index]._playerScore = playerScore;
        index += 1;
    }
    */
}

void Player::addPlayer(int model)
{
    if(model == 0){
        _onlyComputerPlayer = false;
    }
    PlayerInformation player;
    player._playerModel = model;
    player._playerNumber = _amountPlayers;
    player._playerScore = 0;
    _players.push_back(player);
    _amountPlayers += 1;
}

void Player::setActivePlayerByRoundNumber(int roundNumber)
{
    _activePlayer = roundNumber % _amountPlayers;
}

void Player::changePlayer(int number, int model)
{
    if(model == 0){
        _onlyComputerPlayer = false;
    }
    PlayerInformation player;
    player._playerModel = model;
    player._playerNumber = number;
    player._playerScore = 0;
    _players[number] = player;
}

int Player::getWinnerNumber() // return tuple or PlayerInformation?
{
    /*
    for(PlayerInformation player: _players){
        //if(player._playerScore >= 1){     // do we always have a winner if score >= 1?
        if(_gameOver){
            _winner = &player;            // check reference handling
            _gameOver = true;
            return player._playerNumber;	//only return playerNumber? what about score??
        }
    }
    return -1;
    */
    /*
//    std::cout << "test this!" << std::endl;
    double highScore = 0;
    if(_gameOver){
        //if(_winner){             // test this
        //    return _winner->_playerNumber;
        //}
        for(PlayerInformation& player: _players){
            if(player._playerScore > highScore){
                _winner = &player;            // check reference handling // probably points to garbage after for-iteration.
//                _gameOver = true;
                highScore = player._playerScore;
            }
        }
        if(highScore > 0){
            return _winner->_playerNumber;
        }
    }
    return -1;
    */
    //if (_winner->playerScore < 0){
    assert(_gameOver);
    if(_winner){
        return _winner->_playerNumber;
    }
    else{
        _draw = true;
        std::cout << "what happens if we reach a draw?" << std::endl;
        return -1;
    }
}

double Player::getWinnerScore()
{
    assert(_gameOver);
    if (_winner){
        //std::cout << "winner Score: " << _winner->_playerScore << std::endl;
        return _winner->_playerScore;
    }
    else{
        _draw = true;
        std::cout << "what happens if we reach a draw?" << std::endl;
        return 0;
    }
}

void Player::endGame(std::vector<double> score)
{
    _gameOver = true;
    if (score.empty()){
        return;
    }
    //std::cout << "score.size(): " << score.size() << " _player.size(): " << _players.size() << std::endl;
    if(score.size() != _players.size()){
        std::cout << "score.size" << score.size() << "_players.size()" << _players.size() << std::endl;
        std::cout << "ERROR ERROR ERROR !!!" << std::endl;
    }
    // make a playerScore list in Player(not PlayerInformation). so this function has only to replace that score-vector!!!
    int index = 0;
    for(double playerScore : score){
        _players[index]._playerScore = playerScore;
        index += 1;
    }
    double highScore = 0;
//    if(_gameOver){
        for(PlayerInformation& player: _players){
            if(player._playerScore > highScore){
                _winner = &player;            // check reference handling // probably points to garbage after for-iteration.
//                _gameOver = true;
                highScore = player._playerScore;
            }
        }
        if(highScore > 0){
        //    return _winner->_playerNumber;
        }
//    }
    //return -1;
}

bool Player::isOver()
{
    return _gameOver;
    //std::cout << "not yet implemented" << std::endl;
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
    if (_activePlayer >= _amountPlayers){
        _activePlayer = 0;
    }
}

void Player::resetGame()
{
    _gameOver = false;  // test this?
    _draw = false;
    _activePlayer = 0;
    for(PlayerInformation player : _players){
        player._playerScore = 0;
    }
}


////////////////////////////////////////////////////////
/// \brief PlayerInformation::PlayerInformation
///

PlayerInformation::PlayerInformation()
{
    _playerScore = 0;  // add _playerNumber and score?
    _removed = false;
}
