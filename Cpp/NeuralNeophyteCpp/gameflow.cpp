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
        SaveList* saveList = new SaveList();  //TODO pointer or normal?
    }
    else{
        std::vector<int> gamePath = {};
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

        if (saveTheGAme) {
            //_tree->cutRoot(position);
        }
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
