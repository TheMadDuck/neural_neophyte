#include "traintestvalidate.h"


TrainTestValidate::TrainTestValidate()
{

}

std::array<SaveList*, 3> TrainTestValidate::run(GameFlow *gameFlow, int numberTrain, int numberTest, int numberValidate, int numberModels)
{
    std::array<SaveList*, 3> dataset;
    SaveList* winnersTrain = new SaveList();
    for (int i = 0; i < numberTrain; ++i) {
        if (i % 100 == 0) {
            std::cout << "train-set number: " << i << std::endl;
        }
        int KI_One = _nRand.nRand(numberModels);
        int KI_Two = _nRand.nRand(numberModels);

        gameFlow->resetGame();
        std::vector<int> players{KI_One, KI_Two};
        gameFlow->runGameFlow(players, {}, winnersTrain);
//        gameFlow->runGameFlow(std::vector<int> {KI_One, KI_Two},{}, winnersTrain);

    }
    dataset[0] = winnersTrain;

    SaveList* winnersTest = new SaveList();
    for (int i = 0; i < numberTest; ++i) {
        if (i % 100 == 0) {
            std::cout << "test-set number: " << i << std::endl;
        }
        int KI_One = _nRand.nRand(numberModels);
        int KI_Two = _nRand.nRand(numberModels);

        gameFlow->resetGame();
        std::vector<int> players{KI_One, KI_Two};
        gameFlow->runGameFlow(players,{}, winnersTest);

    }
    dataset[1] = winnersTest;

    SaveList* winnersValidate = new SaveList();
    for (int i = 0; i < numberValidate; ++i) {
        if (i % 100 == 0) {
            std::cout << "Validate-set number: " << i << std::endl;
        }
        int KI_One = _nRand.nRand(numberModels);
        int KI_Two = _nRand.nRand(numberModels);

        gameFlow->resetGame();
        std::vector<int> players{KI_One, KI_Two};
        gameFlow->runGameFlow(players,{}, winnersValidate);

    }
    dataset[2] = winnersValidate;
    delete winnersTrain;
    delete winnersTest;
    delete winnersValidate;
    return dataset;
}
