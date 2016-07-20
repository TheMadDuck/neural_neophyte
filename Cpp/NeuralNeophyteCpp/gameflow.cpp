#include "gameflow.h"
#include <iostream>

GameFlow::GameFlow(LogisticSgd classifier, FourInARow *gameLogic, Field *field, int roundNumber, int amountRandom, Tree *tree)
    :_classifier(classifier), _gameLogic(gameLogic), _field(field), _roundNumber(roundNumber), _amountRandom(amountRandom), _tree(tree)
{
    std::random_device a;
    int i = a();
    std::cout << " i: " << i << std::endl;
}

int GameFlow::AI_Move(int playerNumber, std::vector<int> legalMoves, std::vector<int> players, float randomMoveProba, bool saveTheGame)
{
    //TODO: test whole function!!!
    std::mt19937 rd(seed());
    std::uniform_real_distribution<float> randomDistrib(0,1);
    if (randomDistrib(rd) < randomMoveProba) {
        std::uniform_int_distribution<int> randomDistrib(0, legalMoves.size());
        return legalMoves[randomDistrib(rd)];
    }
    if (players[playerNumber-1] == 0) {
        std::uniform_int_distribution<int> randomDistrib(0, legalMoves.size());
        return legalMoves[randomDistrib(rd)];
    }

    std::vector<int> flatField = _field->flatten();
    flatField.push_back(playerNumber);
    flatField.push_back(_roundNumber);

    if(saveTheGame == true){
        MinMaxPruning minMaxPruning;
        if (players[0] == -1) {
            std::vector<int> p {players[1], players[1]};
            return minMaxPruning.exploited_mcts(_field, _tree, legalMoves, _classifier, p, _roundNumber, playerNumber, 0.2);
        }
        if (players[1] == -1){
            std::vector<int> p {players[0], players[0]};
            return minMaxPruning.exploited_mcts(_field, _tree, legalMoves, _classifier, p, _roundNumber, playerNumber, 0.2);
        }
        return minMaxPruning.exploited_mcts(_field, _tree, legalMoves, _classifier, players, _roundNumber, playerNumber, 0.2);
    }
    return _classifier.predict(flatField, players[playerNumber-1]-1)[0];
}


int GameFlow::Human_Move(std::vector<int> legalMoves)
{
    int move;
    std::cout << "Which move do you want to make? [";
    for (auto number : legalMoves) {
        std::cout << number << ", ";
    }
    std::cout << "]" << std::endl;

    while(true){
        std::cin >> move;

        for(auto var: legalMoves) {
            if (var == move) {
                return move;
            }
        }

        std::cout << "Press ";
        for (auto number : legalMoves) {
            std::cout << number << ", ";
        }
        std::cout << std::endl;

    }
}



std::vector<int> GameFlow::runGameFlow(std::vector<int> player, bool saveTheGAme, std::vector<int> prefixPath)
{

    if(saveTheGAme){
        saveList = new SaveList();  //TODO pointer or normal?
    }
    else{
        gamePath = {};
    }
    if (!prefixPath.empty()) {
        int preWinner = addPrefixPath(prefixPath);
        std::vector<int> gamePath = prefixPath;
        if (preWinner) {
            return gamePath;
        }
    }

    std::vector<int> legalInputs = _gameLogic->getLegalInputs();
    if(_gameLogic->getSignal() != "legal_inputs_initialized"){
        std::cout << "ERROR: legal inputs could not get initialized" << std::endl;
    }

    if(_field = nullptr){ //testen
        _field = _gameLogic->initField();
        if (_gameLogic->getSignal() != "field_initialized") {
            std::cout << "ERROR: Field could not get initialized" << std::endl;
        }
    }

    while((_gameLogic->getSignal() != "we_have_a_winner") || (_gameLogic->getSignal() != "game_is_over")){
        int playerNumber;
        if (_roundNumber % 2 == 0) {
            playerNumber = 1;
        }
        else{
            playerNumber = 2;
        }

        int position;
        if (player[playerNumber - 1] == -1) {
            position = Human_Move(legalInputs);
        }
        else{
            position = AI_Move(playerNumber, legalInputs, player, _amountRandom, saveTheGAme);
        }

        if (saveTheGAme) {  // hier an richtiger stelle?
            _tree->cutRoot(position);
        }
        _gameLogic->isLegalMove(_field, playerNumber, position);

        while((_gameLogic->getSignal() == "unvalid_player")
              || (_gameLogic->getSignal() == "unvalid_position")
              || (_gameLogic->getSignal() == "column_is_full")){
            _gameLogic->gameStopped(_field, _roundNumber);
            if(_gameLogic->getSignal() == "game_is_over"){
                break;
            }

            if (player[playerNumber - 1] == -1) {
                std::cout << "this move is not legal, please try again!!" << std::endl;
                position = Human_Move(legalInputs);
            }
            else{
                position = AI_Move(playerNumber, legalInputs, player, 1, saveTheGAme);
            }

            if (saveTheGAme) {
                _tree->cutRoot(position);
            }
            _gameLogic->isLegalMove(_field, playerNumber, position);
        }

        if(saveTheGAme){
            saveList->savePositions(*_field, playerNumber, _roundNumber, position, false); //reference to _field ??
        }
        else{
            gamePath.push_back(position);
        }
        _gameLogic->setstone(_field, playerNumber, position);
        if (_gameLogic->getSignal() != "stone_is_set") {
            std::cout << "ERROR: Stone is not saved" << std::endl;
        }
        if((player[0] == -1) || (player[1] == -1)){
            std::cout << "\n" << _field << std::endl;
        }
        _winner = _gameLogic->hasAWinner(_field, playerNumber, position);
        if (_gameLogic->getSignal() == "we_have_a_winner") {
            if (_winner == 0) {
                std::cout << "ERROR: we could not determine who won!" << std::endl;
            }
            if((player[0] == -1) || (player[1] == -1)){
                std::cout << "\n" << "the winner is: " << _winner << std::endl;
            }
            break;
        }
        _gameLogic->gameStopped(_field, _roundNumber);
        if(_gameLogic->getSignal() == "game_is_over"){
            break;
        }
        _roundNumber += 1;
    }
    if(saveTheGAme){
        /*if (_winner-1 == 0) {
            saveList->
        }
        return saveList[_winner-1];*/
    }
    else {
        return gamePath;
    }

    std::cout << "testaa" << std::endl;
}

int GameFlow::getWinner()
{
    return _winner;
}

void GameFlow::resetGame()
{
    _field = nullptr; //TODO: ja?
    _roundNumber = 0;
}

int GameFlow::addPrefixPath(std::vector<int>)
{

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
