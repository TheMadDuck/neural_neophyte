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

#include "pegsolitaire.h"

PegSolitaire::PegSolitaire()
{
}

PegSolitaire::~PegSolitaire()
{

}

std::string PegSolitaire::getSignal()
{
    return Signal;
}

std::string PegSolitaire::getName()
{
    return "peg_solitaire";
}

int PegSolitaire::positionVectorSize()
{
    return 3;
}

std::vector<Position> PegSolitaire::getLegalInputs(Field *field)
{
    _field = field;
    _legal_inputs.clear();
    for(int i = 0; i < field->getHeight(); ++i){
        for(int j = 0; j < field->getWidth(); ++j){
            if (field->get(i, j) == 1){
                addDirection(i, j);
            }
        }
    }
    Signal = "legal_inputs_initialized";
    return _legal_inputs;
}

Field *PegSolitaire::initField(int height, int width)
{
    Field* field = new Field({{3, 3, 3, 1, 1, 1, 3, 3, 3},
                            {3, 3, 3, 1, 1, 1, 3, 3, 3},
                            {3, 3, 3, 1, 1, 1, 3, 3, 3},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1},
                            {1, 1, 1, 1, 0, 1, 1, 1, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1},
                            {3, 3, 3, 1, 1, 1, 3, 3, 3},
                            {3, 3, 3, 1, 1, 1, 3, 3, 3},
                            {3, 3, 3, 1, 1, 1, 3, 3, 3}});
    Signal = "field_initialized";
    return field;
}

void PegSolitaire::setStone(Field *field, int color, Position position)
{
    field->set(0 ,position[0], position[1]);
    switch(position[2]){
    case up: field->set(0, position[0]-1, position[1]);
        field->set(1, position[0]-2, position[1]);
        break;
    case down: field->set(0, position[0]+1, position[1]);
        field->set(1, position[0]+2, position[1]);
        break;
    case left: field->set(0, position[0], position[1]-1);
        field->set(1, position[0], position[1]-2);
        break;
    case right: field->set(0, position[0], position[1]+1);
        field->set(1, position[0], position[1]+2);
        break;
    }
    Signal = "stone_is_set";
}

bool PegSolitaire::gameStopped(Field *field, int roundNumber)
{
    getLegalInputs(field);
    if(_legal_inputs.empty()){
        Signal = "game_is_over";
        return true;
    }
    return false;
}

int PegSolitaire::hasAWinner(Field *field, int color, Position position)
{
    getLegalInputs(field);
    if(_legal_inputs.empty()){
        Signal = "we_have_a_winner";
        return 1;
    }
    return 0;
}

int PegSolitaire::numberPlayers()
{
    return 1;
}

std::vector<double> PegSolitaire::getPlayerScore(Field *field)
{

}

PegSolitaire::addDirection(int i, int j)
{
    if(isInField(i+1, j)){ // ugly code
        if(_field->get(i+1, j) == 1){
            if(isInField(i+2, j)){
                if(_field->get(i+2,j) == 0){
                    Position newPosition;
                    newPosition.setPositionVector({i, j, down});
                    _legal_inputs.push_back(newPosition);
                }
            }
        }
    }
    if(isInField(i-1, j)){
        if(_field->get(i-1, j) == 1){
            if(isInField(i-2, j)){
                if(_field->get(i-2,j) == 0){
                    Position newPosition;
                    newPosition.setPositionVector({i, j, up});
                    _legal_inputs.push_back(newPosition);
                }
            }
        }
    }
    if(isInField(i, j+1)){
        if(_field->get(i, j+1) == 1){
            if(isInField(i, j+2)){
                if(_field->get(i,j+2) == 0){
                    Position newPosition;
                    newPosition.setPositionVector({i, j, right});
                    _legal_inputs.push_back(newPosition);
                }
            }
        }
    }
    if(isInField(i, j-1)){
        if(_field->get(i, j-1) == 1){
            if(isInField(i, j-2)){
                if(_field->get(i,j-2) == 0){
                    Position newPosition;
                    newPosition.setPositionVector({i, j, left});
                    _legal_inputs.push_back(newPosition);
                }
            }
        }
    }
}

bool PegSolitaire::isInField(int i, int j)
{
    /*
    if(i >= 0 && i <= 8 && j>= 0 && j <= 8){
        if(i <= 2 && j <= 2){
            return false;
        }
        if(i >= 6 && j <= 2){
            return false;
        }
        if(i <= 2 && j >= 6){
            return false;
        }
        if(i >= 6 && j >= 6){
            return false;
        }
        return true;
    }
    return false;
    */

    if(i >= 0 && i <= 8 && j>= 0 && j <= 8 && _field->get(i, j) != 3){
        return true;
    }
    return false;
}
