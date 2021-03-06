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

#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include "../data_types/field.h"
#include "../data_types/position.h"
#include "../data_types/player.h"
class Game
{
public:
    Game();
    ~Game();
    virtual std::string getSignal() =0;
    virtual std::string getName() =0;
    virtual int positionVectorSize() =0;
    virtual std::vector<Position> getLegalInputs(Field* field, int activePlayer = 0) =0; // make parameter const?!
    //virtual std::vector<Position> getLegalInputs(Field* field, Player* player) =0; // make parameter const?!
    virtual Field* initField(int height = 6, int width = 7) =0;
    virtual void setStone(Field *field, int color, Position position) =0;
    virtual bool gameStopped(Field *field, int roundNumber, std::vector<Position> legal_inputs, Position lastMove) =0;
    virtual int numberPlayers() =0;
    virtual std::vector<double> getPlayerScore(Field *field, int color, Position lastMove) =0; // 0:= player lost. 1:= player won. between 0-1: bad to god. (could replace hasAWinner) First entry in array for GameFinishedYet.
    //virtual std::vector<double> getPlayerScore(Field *field, Player* player, Position position, bool gameCompleted) =0; // 0:= player lost. 1:= player won. between 0-1: bad to god. (could replace hasAWinner) First entry in array for GameFinishedYet.
protected:
    std::string Signal = "";
private:
    //Field* _field;
};

#endif // GAME_H
