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
