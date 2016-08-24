#include "menu.h"

#include <iostream>
#include <array>

Menu::Menu()
{
    gameLogic = new FourInARow();

    /*
    Field * field = gameLogic->initField();
    gameLogic->isLegalMove(field,1,4);
    gameLogic->setstone(field,2,4);
    gameLogic->gameStopped(field, 22);
    gameLogic->hasAWinner(field, 2, 3);
    field->showField();
*/
    gameFlow = new GameFlow(classifier, gameLogic);

    std::cout << "Play a Game (press 1)" << std::endl;
    std::cout << "Train the AI (press 2)" << std::endl;
    std::cout << "Sort existing classifiers and rank them (press 3)" << std::endl;
    std::cout << "\n";
    std::cin >> mode;
    std::cout << "your number was: " << mode << std::endl;
    while ((mode != 1) && (mode != 2) && (mode != 3)){
        std::cout << "press 1, 2 or 3" << std::endl;
        std::cin >> mode;
    }


    gameName = gameLogic->getName();

    numberModels = modelHandler.loadBestModel(classifier, gameName);


    if (mode == 1){
        std::cout << ("do you want to be player 1 or player 2?") << std::endl;
        std::cin >> humanPlayerNumber;
        while((humanPlayerNumber != 1) && (humanPlayerNumber != 2)){
            std::cout << ("Press 1 or 2!: ") << std::endl;
            std::cin >> humanPlayerNumber;
        }
        if (humanPlayerNumber == 1){
            std::vector<int> player {-1, numberModels};
//            gameFlow->runGameFuulow(std::array<int, 2>{2, 3});
            SaveList* saveList = new SaveList();
            gameFlow->runGameFlow(player,{}, saveList); //TODO: remove saveList
        }
        else{
            gameFlow->runGameFlow(std::vector<int>{numberModels, -1});
        }

    }

    if (mode == 2){
        TrainTestValidate gameTTV;
        gameTTV.run(gameFlow, 400, 100, 100, numberModels);
        std::string bestModelPath = "./best_models" + gameName + "best_model_" + std::to_string(numberModels) + ".pkl";
        classifier.fit();
    }

    if (mode == 3){
        std::cout << "How many games should be played?" << std::endl;
        int amountGames;
        std::cin >> amountGames;
        EloRanking eloRanking;
        eloRanking.turnier(gameFlow, amountGames, numberModels, gameName);
    }
    delete gameLogic;
    delete gameFlow;
}
