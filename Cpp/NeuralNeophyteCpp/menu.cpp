#include "menu.h"

#include <iostream>
#include <array>

Menu::Menu()
{
    _gameLogic = new FourInARow();

    /*
    Field * field = gameLogic->initField();
    gameLogic->isLegalMove(field,1,4);
    gameLogic->setstone(field,2,4);
    gameLogic->gameStopped(field, 22);
    gameLogic->hasAWinner(field, 2, 3);
    field->showField();
*/
    Tree* tree = new Tree;
    _gameFlow = new GameFlow(_classifier, _gameLogic, nullptr, tree);

    std::cout << "Play a Game (press 1)" << std::endl;
    std::cout << "Train the AI (press 2)" << std::endl;
    std::cout << "Sort existing classifiers and rank them (press 3)" << std::endl;
    std::cout << "\n";
    std::cin >> _mode;
    std::cout << "your number was: " << _mode << std::endl;
    while ((_mode != 1) && (_mode != 2) && (_mode != 3)){
        std::cout << "press 1, 2 or 3" << std::endl;
        std::cin >> _mode;
    }


    _gameName = _gameLogic->getName();

    _numberModels = _modelHandler.loadBestModel(_classifier, _gameName);


    if (_mode == 1){
        std::cout << ("do you want to be player 1 or player 2?") << std::endl;
        std::cin >> _humanPlayerNumber;
        while((_humanPlayerNumber != 1) && (_humanPlayerNumber != 2)){
            std::cout << ("Press 1 or 2!: ") << std::endl;
            std::cin >> _humanPlayerNumber;
        }
        if (_humanPlayerNumber == 1){
            std::vector<int> player {0, _numberModels};
//            _gameFlow->runGameFuulow(std::array<int, 2>{2, 3});
            SaveList* saveList = new SaveList();
            _gameFlow->runGameFlow(player,{}, saveList); //TODO: remove saveList
            delete saveList;
        }
        else{
            _gameFlow->runGameFlow(std::vector<int>{_numberModels, 0});  //here for testing purposes -2 (for mcts)
        }

    }

    if (_mode == 2){
        TrainTestValidate gameTTV;
        std::array<SaveList*, 3> TTV_Data = gameTTV.run(_gameFlow, 400, 100, 100, _numberModels);
        std::string bestModelPath = "./best_models" + _gameName + "best_model_" + std::to_string(_numberModels) + ".pkl";
        _classifier.fit();
    }

    if (_mode == 3){
        std::cout << "How many games should be played?" << std::endl;
        int amountGames;
        std::cin >> amountGames;
        EloRanking eloRanking;
        eloRanking.turnier(_gameFlow, amountGames, _numberModels, _gameName);
    }
    tree->deleteTree(tree);
    delete _gameLogic;
    delete _gameFlow;
}
