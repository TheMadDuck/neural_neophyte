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

#ifndef PEGSOLITAIRE_H
#define PEGSOLITAIRE_H

#include "game.h"
#include <string>
#include <vector>
class PegSolitaire : public Game
{
public:
    PegSolitaire();
    ~PegSolitaire();
    std::string getSignal() override;
    std::string getName() override;
    int positionVectorSize() override;
    std::vector<Position> getLegalInputs(Field* field) override;
    Field* initField(int height = 6, int width = 7) override;
    //bool isLegalMove(Field *field, int playerNumber, Position position) override;
    void setStone(Field *field, int color, Position position) override;
    bool gameStopped(Field *field, int roundNumber) override;
    //int hasAWinner(Field *field, int color, Position position) override;
    int numberPlayers() override;
    std::vector<double> getPlayerScore(Field *field, int color, Position position) override;

private:
    std::string Signal = ""; // define Signal in Game.h ??
    std::vector<Position> _legal_inputs;
    Field* _field;

    addDirection(int i, int j);
    bool isInField(int i, int j);

    enum directions {up = 1, down = 2, left = 3, right = 4};
};

#endif // PEGSOLITAIRE_H
