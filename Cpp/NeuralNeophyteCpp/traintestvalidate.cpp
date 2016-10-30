#include "traintestvalidate.h"


TrainTestValidate::TrainTestValidate()
{

}

SaveList* TrainTestValidate::provideGameLists(GameFlow *gameFlow, int numberGames, int numberModels)
{
    SaveList* winnersList = new SaveList();
    for (int i = 0; i < numberGames; ++i) {
        if (i % 100 == 0) {
            std::cout << "Game Number: " << i << std::endl;
        }
        int KI_One = _nRand.nRand(numberModels);
        int KI_Two = _nRand.nRand(numberModels);

        gameFlow->resetGame();
        std::vector<int> players{KI_One, KI_Two};
        gameFlow->runGameFlow(players, {}, winnersList);
//        gameFlow->runGameFlow(std::vector<int> {KI_One, KI_Two},{}, winnersTrain); //TODO look for savelist

    }
    return winnersList;
}

std::array<SaveList*, 3> TrainTestValidate::run(GameFlow *gameFlow, int numberTrain, int numberTest, int numberValidate, int numberModels)
{
    std::array<SaveList*, 3> dataset;
    dataset[0] = provideGameLists(gameFlow, numberTrain, numberModels);
    dataset[1] = provideGameLists(gameFlow, numberTest, numberModels);
    dataset[2] = provideGameLists(gameFlow, numberValidate, numberModels);

    return dataset;
}
