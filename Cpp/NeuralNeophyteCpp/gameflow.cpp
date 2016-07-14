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



void GameFlow::runGameFlow(std::vector<int> player, bool saveTheGAme, std::vector<int> prefixPath)
{
    std::cout << "testaa" << std::endl;
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
