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

#include "gameflow.h"
#include <iostream>
#include <assert.h>
//#include "Tests/randomtest.h"

GameFlow::GameFlow(Classifier* classifier, Game *gameLogic, Field *field, Tree *tree, int roundNumber, int amountRandom, NRandomDistrib *nRd, std::vector<Position> gamePath)
    :_classifier(classifier), _gameLogic(gameLogic), _field(field), _roundNumber(roundNumber), _amountRandom(amountRandom), _tree(tree), _nRd(nRd), _gamePath(gamePath)
{
    //_rd.seed(std::time(NULL));
    //_winner = -1;  // -1 for 'there is no winner yet' TODO: make _winner a type.

    _nextPosition.setVectorSize(_gameLogic->positionVectorSize());
}

GameFlow::~GameFlow()
{
    //delete _field;
    //_tree->deleteTree(_tree);
    //    delete _tree;
}


void GameFlow::move()
{
    if (_players->getActiveModel() == 0){
        Human_Move();
        //if (std::find(_legalMoves.begin(), _legalMoves.end(), _nextPosition) != _legalMoves.end()){ // already tested in human_move, but nice algo
        //}
    }
    else{
        //_field->showField();
        AI_Move();
    }

    while((_gameLogic->getSignal() == "unvalid_player")
          || (_gameLogic->getSignal() == "unvalid_position")
          || (_gameLogic->getSignal() == "column_is_full")){

        _gameLogic->gameStopped(_field, _roundNumber);
        if(_gameLogic->getSignal() == "game_is_over"){
            break;
        }

        if(_players->getActiveModel() == 0){
            std::cout << "this move is not legal, please try again!!" << std::endl;
            Human_Move();
        }
        else{
            AI_Move();
        }

    }
    //return _nextPosition;          // Todo: check speed limitation?
}


void GameFlow::AI_Move()
{
    std::uniform_real_distribution<float> randomDistrib(0,1);
    if (randomDistrib(_rd) < _amountRandom) {
        std::cout << "totaly random move !!!" << std::endl;
        _nextPosition = _legalMoves[_nRd->getRandomInt(0, _legalMoves.size()-1)];
        return;
        //return _legalMoves[_nRd->getRandomInt(0, legnnalMoves.size()-1)];
    }

    if(_players->getActiveModel() == -1){
        _nextPosition = _legalMoves[_nRd->getRandomInt(0, _legalMoves.size()-1)];
        return;
        //return _legalMoves[_nRd->getRandomInt(0, _legalMoves.size()-1)];
    }

    std::vector<int> flatField = _field->flatten();
    flatField.push_back(_players->getActivePlayerNumber());
    flatField.push_back(_roundNumber);

    if(_players->getActiveModel() == -2){
        std::cout << "new min max step" << std::endl;
        MinMaxPruning minMaxPruning(_gameLogic->getName());
        _nextPosition = minMaxPruning.exploited_mcts(_field, _tree, _classifier, _roundNumber, _players->getActivePlayerNumber(), _gamePath, 0.2, _nRd, _legalMoves.size());
        return;
        //return minMaxPruning.exploited_mcts(_field, _tree, _classifier, _players, _roundNumber, _playerNumber, _gamePath, 0.2, _nRd);
    }

    if(_players->getActiveModel() == 1){
        // possibility 1
        /*
        int oldScore = 0;
        for(auto move: _legalMoves){
            copy field;
            _gameLogic->setStone(_field, _players->getActivePlayerNumber(), move);
            newScore = _classifier->predict(flatField, _players->getActiveModel()-1);
            if (newScore >= oldScore){
                _nextPosition = move;
            }
        }
        */

        //possibility 2
//        double thisPlayersScore = _classifier->predict(flatField, _players->getActiveModel()-1);
//        _players->setScore(thisPlayersScore, 1- thisPlayersScore, ...);
//        _players->gameIsOver();

        //possibility 3
        //_nextPosition = _classifier->predict(flatField, _players->getActiveModel()-1)[0];   /// TEST! really -1 or just getActiveNumber?
        return;
    }
}


void GameFlow::Human_Move()
{
    //int move;
    std::cout << "Which move do you want to make? [";
    for (Position number : _legalMoves) {
        number.printPosition();
        std::cout << ",  ";
    }
    std::cout << "]" << std::endl;
    while(true){
        _nextPosition.inputPosition();

        for(auto var: _legalMoves) {
            if (var == _nextPosition) {
                return;
                //return _nextPosition;
            }
        }

        std::cout << "Press ";
        for (Position number : _legalMoves) {
            number.printPosition();
            std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
}


// 0= human; negative= conservative-AI-Models[random, mcts..]; positive= NN-AI-Models
std::vector<Position> GameFlow::runGameFlow(Player *players, std::vector<Position> prefixPath, SaveList *saveList)
{
    _players = players;

    if (!prefixPath.empty()) { 
        int preWinner = addPrefixPath(prefixPath);
        if (preWinner != -1) {
            return _gamePath;
        }
    }

    //TODO: initField in the resetGame()?!

    if(!_field){
        _field = _gameLogic->initField();
        if (_gameLogic->getSignal() != "field_initialized") {
            std::cout << "ERROR: Field could not get initialized" << std::endl;
        }
    }
    while(true){
        _legalMoves = _gameLogic->getLegalInputs(_field);
        if(_gameLogic->getSignal() != "legal_inputs_initialized"){
            std::cout << "ERROR: legal inputs could not get initialized" << std::endl;
        }
        move();
        if(saveList){
            saveList->savePositions(*_field, _players->getActivePlayerNumber(), _roundNumber, _nextPosition, false); //reference to _field ??
        }
        _gamePath.push_back(_nextPosition);

        _gameLogic->setStone(_field, _players->getActivePlayerNumber(), _nextPosition);
        if (_gameLogic->getSignal() != "stone_is_set") {
            std::cout << "ERROR: Stone is not saved" << std::endl;
        }
        if(!_players->onlyComputerPlayer()){// in Human_Move?
            std::cout << "Last Move: " << std::endl;
            _nextPosition.printPosition();
            std::cout << "\n";
            _field->showField();
        }
        _players->setScore(_gameLogic->getPlayerScore(_field, _players->getActivePlayerNumber(), _nextPosition));
        if (_gameLogic->getSignal() == "game_is_over") {
            _players->endGame();
            if (_players->getWinnerNumber() == -1) {
                std::cout << "ERROR: we could not determine who won!" << std::endl;
            }
            if(!_players->onlyComputerPlayer()){
                std::cout << "\n" << "The winner is: Player " << _players->getWinnerNumber() +1 << std::endl;
            }
            return _gamePath;
        }
        _players->nextPlayer();
        _roundNumber += 1;
        _gameLogic->gameStopped(_field, _roundNumber);
        if(_gameLogic->getSignal() == "game_is_over"){
            _players->endGame();
            return _gamePath;
        }
    }
    _players->endGame();
    return _gamePath;
}

int GameFlow::getWinner()
{
//    return _winner;
    _players->getWinnerNumber();
}

void GameFlow::resetGame()
{
    _field = _gameLogic->initField();
    _roundNumber = 0;
    //_winner = -1;
    _gamePath = {};
    _players->resetGame();
}

int GameFlow::addPrefixPath(std::vector<Position> prefixPath)
{
    int prefixPathSize = prefixPath.size();
    int pathPosition = 0;
    while(true){
        if(pathPosition >= prefixPathSize){
            return -1; //if there is no winner -1 is returned
        }

        _nextPosition = prefixPath[pathPosition];

        _gameLogic->setStone(_field, _players->getActivePlayerNumber(), _nextPosition);
        _gamePath.push_back(_nextPosition);
        if(_gameLogic->getSignal() != "stone_is_set"){
            std::cout << "ERROR: Stone is not saved" << std::endl;
        }
        _players->setScore(_gameLogic->getPlayerScore(_field, _players->getActivePlayerNumber(), _nextPosition));
        if(_gameLogic->getSignal() == "game_is_over"){
            _players->endGame();
            if(_players->getWinnerNumber() == -1){
                std::cout << "ERROR: We could not determine who won!" << std::endl;
            }
            return getWinner();
        }
        _gameLogic->gameStopped(_field, _roundNumber);
        if (_gameLogic->getSignal() == "game_is_over"){
            _players->endGame();
            return getWinner();
        }
        _players->nextPlayer();
        _roundNumber += 1;
        pathPosition += 1;
    }
    _players->endGame();
    return getWinner();

}


void GameFlow::test()
{
    std::mt19937 rd(seed()); //TODO: realy set every time a new seed ??
    std::cout << seed() << "\n";
    std::cout << seed() << "\n";
    std::uniform_real_distribution<float> rdist(0,1);
    for (int i = 0; i < 12; ++i) {
        std::cout << rdist(rd) << std::endl;
    }
}


void GameFlow::test2()
{
    std::mt19937 rd(seed());
    std::uniform_real_distribution<float> rdist(0,1);
    for (int i = 0; i < 12; ++i) {
        std::cout << rdist(rd) << std::endl;
    }
}
