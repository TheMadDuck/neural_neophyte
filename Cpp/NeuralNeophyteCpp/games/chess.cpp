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

std::vector<Position> Chess::getLegalInputs(Field* field, int activePlayer) // work with field (not with _field). field should exist only extern in gameflow!
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
                case rookB: addRookMoves(i, j, rookB); // if(newPosition.setPositionVector({i, j, rookB, /* where to?*/});
                case knightB: addKnightMoves(i, j, knightB);
                case bishopB: addBishopMoves(i, j, bishopB);
                case queenB: addQueenMoves(i, j, queenB);
                case kingB: addKingMoves(i, j, kingB);
                case pawnB: addPawnMoves(i, j, pawnB);

                case rookW: addRookMoves(i, j, rookW); // if(newPosition.setPositionVector({i, j, rookB, /* where to?*/});
                case knightW: addKnightMoves(i, j, knightW);
                case bishopW: addBishopMoves(i, j, bishopW);
                case queenW: addQueenMoves(i, j, queenW);
                case kingW: addKingMoves(i, j, kingW);
                case pawnW: addPawnMoves(i, j, pawnW);
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

bool Chess::gameStopped(Field *field, int roundNumber, std::vector<Position> legal_inputs, Position lastMove)
{
    //check for draw
}
/*
int Chess::hasAWinner(Field *field, int color, Position position)
{
    // oh shit
    std::vector<std::vector<int>> enemyKingRange;
}
*/
int Chess::numberPlayers()
{
    return 2;
}

std::vector<double> Chess::getPlayerScore(Field *field, int color, Position lastMove)
{
    // oh shit
    Signal = "score_is_set";
    std::vector<std::vector<int>> enemyKingRange;
}

void Chess::addRookMoves(int i, int j, int color)
{
    observeSides(i, j, color, 1, 0);
    observeSides(i, j, color, -1, 0);
    observeSides(i, j, color, 0, -1);
    observeSides(i, j, color, 0, 1);
}

void Chess::addKnightMoves(int i, int j, int color)
{
    std::vector<std::vector<int>> directions = {{2, 1}, {2, -1}, {1, 2}, {1,-2}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1} };
    for(std::vector<int> position : directions){
        if (isInField(i + position[0], j + position[1])){
            Position newPosition;
            newPosition.setPositionVector({i, j, color, i + position[0], j + position[1]});
            _legal_inputs.push_back(newPosition);
        }
    }
}

void Chess::addKingMoves(int i, int j, int color)
{
    std::vector<std::vector<int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for(std::vector<int> position : directions){
        if (isInField(i + position[0], j + position[1])){
            Position newPosition;
            newPosition.setPositionVector({i, j, color, i + position[0], j + position[1]});
            _legal_inputs.push_back(newPosition);
        }
    }
}

void Chess::addBishopMoves(int i, int j, int color)
{
    observeSides(i, j, color, 1, 1);
    observeSides(i, j, color, 1, -1);
    observeSides(i, j, color, -1, 1);
    observeSides(i, j, color, -1, -1);
}

void Chess::addQueenMoves(int i, int j, int color)
{
    observeSides(i, j, color, 1, 0);
    observeSides(i, j, color, -1, 0);
    observeSides(i, j, color, 0, -1);
    observeSides(i, j, color, 0, 1);

    observeSides(i, j, color, 1, 1);
    observeSides(i, j, color, 1, -1);
    observeSides(i, j, color, -1, 1);
    observeSides(i, j, color, -1, -1);
}

void Chess::addPawnMoves(int i, int j, int color)
{
    int direction;
    if(color == pawnB){
        direction = 1;
    }
    else{
        direction = -1;
    }
    if(_turnedField){
        direction *= -1;
    }
    if(isInField(i + direction, j)){
        Position newPosition;
        newPosition.setPositionVector({i, j, color, i + 1, j});
        _legal_inputs.push_back(newPosition);
    }
    //if pawn was not moved yet:
    if(i == 1 && direction == 1){
        Position newPosition;
        newPosition.setPositionVector({i, j, color, i+2, j});
        _legal_inputs.push_back(newPosition);
    }
    if(i == 6 && direction == -1){
        Position newPosition;
        newPosition.setPositionVector({i, j, color, i-2, j});
        _legal_inputs.push_back(newPosition);
    }
    //beat other figure
    std::cout << "not yet implemented" << std::endl;
    // change pawn for other piece
    if(i == 1 && direction == -1){
        Position newPosition;
        std::cout << "not yet implemented" << std::endl;
        newPosition.setPositionVector({i, j, color, });
    }
}

std::vector<int> Chess::getFigurePosition(int figure) // RETURNS ONLY THE FIRST FIGURE!!! SHOULD RETURN POSITION OF EVERY FIGURE
{
    for(int i = 0; i < _field->getHeight(); ++i){
        for(int j = 0; j < _field->getWidth(); ++i){
            if(_field->get(i, j) == figure){
                return {i, j};
            }
        }
    }
}

bool Chess::inCheck(int color)
{
    std::vector<int> coordinates = getFigurePosition(color);
    std::vector<std::vector<int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for(std::vector<int> direction : directions){
        if(kingCheckSides(coordinates[0], coordinates[1], color, direction[0], direction[1])){
            return true;
        }
    }

    directions = {{2, 1}, {2, -1}, {1, 2}, {1,-2}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1} };
    for(std::vector<int> direction : directions){
        if (isInField(coordinates[0] + direction[0], coordinates[1] + direction[1])){ // necessary?

            // ugly?!
            if(color == kingB && _field->get(coordinates[0] + direction[0], coordinates[1] + direction[1]) == knightW){
                return true;
            }
            if(color == kingW && _field->get(coordinates[0] + direction[0], coordinates[1] + direction[1]) == knightB){
                return true;
            }
        }
    }
    /*
    kingCheckSides(coordinates[0], coordinates[1], color, 1, 0); // if one of those returns true, return true
    kingCheckSides(coordinates[0], coordinates[1], color, -1, 0);
    kingCheckSides(coordinates[0], coordinates[1], color, 0, -1);
    kingCheckSides(coordinates[0], coordinates[1], color, 0, 1);
    kingCheckSides(coordinates[0], coordinates[1], color, 1, 1);
    kingCheckSides(coordinates[0], coordinates[1], color, 1, -1);
    kingCheckSides(coordinates[0], coordinates[1], color, -1, 1);
    kingCheckSides(coordinates[0], coordinates[1], color, -1, -1);
    */

}

bool Chess::inCheckMate(int color)
{

}

int Chess::getHashDivisor()
{
    return 12; // max possible value in the position vector (here width and height are 8, but possible figures are 12)
}

void Chess::observeSides(int i, int j, int figure, int topDown, int leftRight)  // rename to:traverse sides
{
    int iNew = i + topDown;
    int jNew = j + leftRight;
    bool freeSpace = true;
    while (isInField(iNew, jNew) && freeSpace){
        if(_field->get(iNew, jNew) != 0){
            freeSpace = false;
        }

        Position newPosition;
        newPosition.setPositionVector({i, j, figure, iNew, jNew});
        _legal_inputs.push_back(newPosition);

        iNew+=topDown;
        jNew+=leftRight;
    }
}

bool Chess::kingCheckSides(int i, int j, int figure, int topDown, int leftRight)
{
    int iNew = i + topDown;
    int jNew = j + leftRight;
    bool freeSpace = true;
    while (isInField(iNew, jNew)){
        int position = _field->get(iNew, jNew);
        if (position == 0){
            continue;
        }
        if(figure == kingB && (position == bishopW || position == rookW || position == queenW)){
            return true;
        }
        if(figure == kingW && (position == bishopB || position == rookB || position == queenB)){
            return true;
        }

        iNew+=topDown;
        jNew+=leftRight;
    }
    return false;
}

bool Chess::isInField(int i, int j)
{
    if(i > -1 && i < 8 && j > 0 && j < 8){
        return true;
    }
    return false;
}

