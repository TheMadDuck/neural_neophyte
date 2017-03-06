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

#include "menu.h"

#include <iostream>
#include <array>
#include "games/fourinarow.h"
#include "games/chess.h"
#include "games/pegsolitaire.h"
#include "games/kalaha.h"

Menu::Menu()
{
    NRandomDistrib nRd;
    std::cout << "What game do you want to play?" << std::endl;
    std::cout << "Play FourInARow (press 1)" << std::endl;
    std::cout << "Play Chess (press 2)" << std::endl;
    std::cout << "Play Peg Solitaire (press 3)" << std::endl;
    std::cout << "Play Kalaha (press 4)" << std::endl;
    std::cout << "End Program (press 5)" << std::endl;
    std::cout << "\n";
    std::cin >> _mode;
    while ((_mode != 1) && (_mode != 2) && (_mode != 3) && (_mode != 4) && (_mode != 5)){
        std::cout << "your number was: " << _mode << std::endl;
        std::cout << "press 1, 2, 3, 4 or 5" << std::endl;
        std::cin >> _mode;
    }
    if(_mode == 1){
        _gameLogic = new FourInARow();
    }
    if(_mode == 2){
        _gameLogic = new Chess();
    }
    if(_mode == 3){
        _gameLogic = new PegSolitaire();
    }
    if(_mode == 4){
        _gameLogic = new Kalaha();
    }
    if(_mode == 5){
        return;
    }

    //_gameLogic = new FourInARow();
    _tree = new Tree(_gameLogic->numberPlayers());
    _gameFlow = new GameFlow(_classifier, _gameLogic, nullptr, _tree, 0, 0.15, &nRd); //do we really want 0.15 randomnes?[test this]
    _gameName = _gameLogic->getName();
    _numberModels = _modelHandler.loadBestModel(_classifier, _gameName);

    std::cout << "Welcome to NeuralNeophyte! The selected game is: " << _gameName << std::endl;
    std::cout << "\n";
    std::cout << "Play a Game (press 1)" << std::endl;
    std::cout << "Train the AI (press 2)" << std::endl;
    std::cout << "Sort existing classifiers and rank them (press 3)" << std::endl;
    std::cout << "End Program (press 4)" << std::endl;
    std::cout << "\n";
    std::cin >> _mode;
    while ((_mode != 1) && (_mode != 2) && (_mode != 3) && (_mode != 4)){
        std::cout << "your number was: " << _mode << std::endl;
        std::cout << "press 1, 2, 3 or 4" << std::endl;
        std::cin >> _mode;
    }
    // todo clear screen


    if (_mode == 1){
        std::cout << "which player do you want to be? bewteen 1 and " << _gameLogic->numberPlayers() << " (0 for only computer)" << std::endl;
        std::cin >> _humanPlayerNumber;

        while(_humanPlayerNumber < 0 || _humanPlayerNumber > _gameLogic->numberPlayers()){
            std::cout << "Press Number from 1 to " << _gameLogic->numberPlayers() << " !: " << std::endl;
            std::cin >> _humanPlayerNumber;
        }
//        std::vector<int> player;
        Player* players = new Player();
        for(int i = 0; i < _gameLogic->numberPlayers(); ++i){
            //player.push_back(_numberModels); // here for testing purpose -2 (for mcts)
            players->addPlayer(_numberModels);
        }
        if(_humanPlayerNumber != 0){ // 0 for only computer
            //player[_humanPlayerNumber-1] = 0;
            players->changePlayer(_humanPlayerNumber-1, 0);
        }
        //return;
        SaveList* saveList = new SaveList();
        std::vector<Position> a = _gameFlow->runGameFlow(players, {}, saveList);
        saveList->printProgress();

        for (Position x: a){
            for(int y : x.getPositionVector()){
                std::cout << y << " ";
            }
            std::cout << std::endl;
        }

//        _gameFlow->runGameFlow(players);
        std::cout << "debug 0" << std::endl;
        //std::cout << "player " << players->getWinnerNumber() << " won with a score of " << players->getWinnerScore() << std::endl; // does only work in two seperate lines?!
        std::cout << "player " << players->getWinnerNumber() << std::endl;
        std::cout << " won with a score of " << players->getWinnerScore() << std::endl;


    }

    if (_mode == 2){
        TrainTestValidate gameTTV;
        std::array<SaveList*, 3> TTV_Data = gameTTV.run(_gameFlow, 400, 100, 100, _numberModels);
        std::string bestModelPath = "./best_models" + _gameName + "best_model_" + std::to_string(_numberModels) + ".pkl";
        _classifier->learn(TTV_Data);
    }

    if (_mode == 3){
        std::cout << "How many games should be played?" << std::endl;
        int amountGames;
        std::cin >> amountGames;
        EloRanking eloRanking;
        eloRanking.turnier(_gameFlow, amountGames, _numberModels, _gameName);
    }

    if (_mode == 4){
        return;
    }
    _tree->deleteTree(_tree);
    delete _gameLogic;
    delete _gameFlow;
}
