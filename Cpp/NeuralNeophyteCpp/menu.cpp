#include "menu.h"

#include <iostream>
#include <array>

Menu::Menu()
{
    gameLogic = new FourInARow();
    gameFlow = new GameFlow();
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
    gameName = gameLogic->get_name();
    //numberModels = modelHandler.loadBestModel(classifier, gameName)
    numberModels = modelHandler.loadBestModel(gameName);

    if (mode == 1){
        std::cout << ("do you want to be player 1 or player 2?") << std::endl;
        std::cin >> humanPlayerNumber;
        while((humanPlayerNumber != 1) && (humanPlayerNumber != 2)){
            std::cout << ("Press 1 or 2!: ") << std::endl;
            std::cin >> humanPlayerNumber;
        }
        if (humanPlayerNumber == 1){
            std::array<int, 2> player {2, 3};
//            gameFlow->run_game_flow(std::array<int, 2>{2, 3});
            gameFlow->run_game_flow(player);
        }
    }
}
