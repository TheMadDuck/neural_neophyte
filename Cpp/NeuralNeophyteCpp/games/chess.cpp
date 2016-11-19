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

#include "chess.h"

Chess::Chess()
{
    _field = nullptr;
}

Chess::~Chess()
{
    delete _field;
}

std::string Chess::getSignal()
{
    return Signal;
}

std::string Chess::getName()
{
    return "chess";
}

int Chess::positionVectorSize()
{
    return 6; // 2 from 1 kindOf 1 color 2 to
}

std::vector<Position> Chess::getLegalInputs()
{
    std::vector<Position> legal_inputs;
    std::cout << "not yet implemented" << std::endl;
}

Field *Chess::initField(int height, int width)
{
    _field = new Field(height, width);
    _field->set(rookB, 0, 0);
    _field->set(knightB, 0, 1);
    _field->set(bishopB, 0, 2);
    _field->set(queenB, 0, 3);
    _field->set(kingB, 0, 4);
    _field->set(bishopB, 0, 5);
    _field->set(knightB, 0, 6);
    _field->set(rookB, 0, 7);

    _field->set(rookW, 7, 0);
    _field->set(knightW, 7, 1);
    _field->set(bishopW, 7, 2);
    _field->set(queenW, 7, 3);
    _field->set(kingW, 7, 4);
    _field->set(bishopW, 7, 5);
    _field->set(knightW, 7, 6);
    _field->set(rookW, 7, 7);
    for(int i = 0; i < 8; ++i){
        _field->set(pawnB, 1, i);
        _field->set(pawnW, 6, i);
    }

    Signal = "field_initialized";
    return _field;
}

bool Chess::isLegalMove(Field *field, int playerNumber, Position position)
{

}

void Chess::setStone(Field *field, int color, Position position)
{
    std::cout << "not yet implemented" << std::endl;
    field->set(0, position[0], position[1]); // old position is now 0.
    field->set(position[2], position[3], position[4]); // new position is now position[2].
    std::cout << "not yet implemented" << std::endl;
}

bool Chess::gameStopped(Field *field, int roundNumber)
{

}

int Chess::hasAWinner(Field *field, int color, Position position)
{

}
