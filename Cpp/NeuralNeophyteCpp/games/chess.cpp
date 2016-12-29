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
    //_field = nullptr;
}

Chess::~Chess()
{
    //delete _field;
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

std::vector<Position> Chess::getLegalInputs(Field* field) // work with field (not with _field). field should exist only extern in gameflow!
{
    _field = field;
    //std::vector<Position> legal_inputs;
    _legal_inputs.clear();  // deletes Positions  (mayby use vector of pointers to positions??)
    for(int i = 0; i < field->getHeight(); ++i){
        for(int j = 0; j < field->getWidth(); ++i){
/*            if(_field[i][j] != 0){
                legal_inputs
            }
*/
            //Position newPosition;
            switch(field->get(i, j)){
                case rookB: addRookMoves(i, j); // if(newPosition.setPositionVector({i, j, rookB, /* where to?*/});
            }
            //legal_inputs.push_back(newPosition);
        }
    }
    std::cout << "not yet implemented" << std::endl;
}

Field *Chess::initField(int height, int width)
{
    Field* field = new Field(height, width);
    field->set(rookB, 0, 0);
    field->set(knightB, 0, 1);
    field->set(bishopB, 0, 2);
    field->set(queenB, 0, 3);
    field->set(kingB, 0, 4);
    field->set(bishopB, 0, 5);
    field->set(knightB, 0, 6);
    field->set(rookB, 0, 7);

    field->set(rookW, 7, 0);
    field->set(knightW, 7, 1);
    field->set(bishopW, 7, 2);
    field->set(queenW, 7, 3);
    field->set(kingW, 7, 4);
    field->set(bishopW, 7, 5);
    field->set(knightW, 7, 6);
    field->set(rookW, 7, 7);
    for(int i = 0; i < 8; ++i){
        field->set(pawnB, 1, i);
        field->set(pawnW, 6, i);
    }

    Signal = "field_initialized";
    return field;
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

std::vector<Position> Chess::getPossibleMove(int height, int width, int figure)
{
    std::vector<Position> moves;
    if (figure == rookB){
//        for (int i = 0; i <8, )
    }
    if (figure == pawnB){
        moves.push_back(Position({height, width, pawnB, height+1, width}));
        if(height == 1){
            moves.push_back(Position({height, width, pawnB, height+2, width}));
        }
    }
}

void Chess::addRookMoves(int i, int j)
{
    int tempPosition = 0;
    int temp = 1;
    while(tempPosition == 0){  // TODO: Test
        tempPosition = _field->get(i + temp, j);
        Position newPosition;
        newPosition.setPositionVector({i, j, rookB, i + temp, j});
        _legal_inputs.push_back(newPosition);
        temp += 1;
    }
}

int Chess::getHashDivisor()
{
    return 12; // max possible value in the position vector (here width and height are 8, but possible figures are 12)
}

