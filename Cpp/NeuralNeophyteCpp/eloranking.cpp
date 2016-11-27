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

#include "eloranking.h"

EloRanking::EloRanking()
{
}

void EloRanking::turnier(GameFlow *gameFlow, int amountGames, int amountModels, std::string gameName)
{
    double eloRank = 1000 * amountModels;
    for (int gameNumber = 0; gameNumber < amountModels; ++gameNumber) {
        NRandomDistrib nRand;
        int KI_One = nRand.nRand(amountModels);
        int KI_Two = nRand.nRand(amountModels);
        gameFlow->resetGame();
        gameFlow->runGameFlow({KI_One, KI_Two}); //test
//        newRanking = naiveElo(eloRank[])
        std::cout << "not yet implemented" << std::endl;
    }
}

std::vector<double> EloRanking::naiveElo(double leftValue, double rightValue, int decition)
{
    double distance = abs(leftValue - rightValue);
    double normedDistance = (distance/5 + 0.1);
    if(decition == 0){ // played a draw
        return {leftValue, rightValue};
    }
    if(decition == 1){
        normedDistance = -normedDistance; //test
    }
    leftValue += normedDistance;
    rightValue -= normedDistance;
    return {leftValue, rightValue};
}
