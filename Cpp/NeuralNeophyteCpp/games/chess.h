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

#ifndef CHESS_H
#define CHESS_H
#include <string>
#include <vector>
#include "game.h"
#include "../field.h"
#include "../data_types/position.h"

class Chess : public Game
{
public:
    //its just the four in a row template
    Chess();
    ~Chess();
    std::string getSignal() override;
    std::string getName() override;
    int positionVectorSize() override;
    std::vector<Position> getLegalInputs() override;
    Field* initField(int height = 8, int width = 8) override;
    bool isLegalMove(Field *field, int playerNumber, Position position) override;
    void setStone(Field *field, int color, Position position) override;
    bool gameStopped(Field *field, int roundNumber) override;
    int hasAWinner(Field *field, int color, Position position) override;

    std::vector<Position> getPossibleMove(int height, int width, int figure);
    int getHashDivisor();

private:
    std::string Signal = "";
    Field* _field;
    enum Figures {rookB = 1, knightB = 2, bishopB = 3, queenB = 4, kingB =5, pawnB =6,
                  rookW = 7, knightW = 8, bishopW = 9, queenW = 10, kingW =11, pawnW = 12};
};

#endif // CHESS_H
