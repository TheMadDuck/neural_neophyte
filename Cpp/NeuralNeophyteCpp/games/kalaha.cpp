/*   Copyright (C) 2017 by Daniel M.H. Noll                                *
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

#include "kalaha.h"

Kalaha::Kalaha()
{
}

Kalaha::~Kalaha()
{

}

std::string Kalaha::getSignal()
{
    return Signal;
}

std::string Kalaha::getName()
{
    return "kalaha";
}

int Kalaha::positionVectorSize()
{
    return 1;
}

std::vector<Position> Kalaha::getLegalInputs(Field *field, int activePlayer)
{
    std::vector<Position> legal_inputs;
    for(int i = 0; i < field->getWidth(); ++i){
        if(activePlayer == 0){
            if(field->get(0, i) != 0){
                legal_inputs.push_back(Position({i}));
            }
        }
        else{
            if(field->get(1, i) != 0){
                legal_inputs.push_back(Position({i}));
            }
        }
    }
    Signal = "legal_inputs_initialized";
    return legal_inputs;
}

Field *Kalaha::initField(int height, int width)
{
    //maybe:
    // 6 5 4 3 2 1 0
    //   0 1 2 3 4 5 6

    // but in code like:
    // 0 1 2 3 4 5 6
    // 0 1 2 3 4 5 6

    height = 2;  // attention: hardcoded!
    width = 6;
    Field* field = new Field(2, 6);
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width-1; ++j){
            field->set(5, i, j);
        }
    }
    Signal = "field_initialized";
    return field;
}

void Kalaha::setStone(Field *field, int color, Position position)
{
    int numberStones = field->get(color, position[0]);
    int player = color;
    int activePosition = position[0];
    while(numberStones > 0){
//        field->set(0, color, position[0]);
        activePosition += 1;
        if (activePosition == 6){
            activePosition = 0;
            if (player == 0){
                player = 1;
            }
            else{
                player = 0;
            }
        }
        field->set(field->get(player, activePosition) +1, player, activePosition);
        numberStones -= 1;
        if(numberStones == 0){
            numberStones = field->get(player, activePosition);
        }
        //break;
    }
    Signal = "stone_is_set";
}

bool Kalaha::gameStopped(Field *field, int roundNumber, std::vector<Position> legal_inputs)
{
    // function the same for all games? into games.cpp? probably not...?
    //getLegalInputs(field);
     if(legal_inputs.empty()){
         Signal = "game_is_over";
         return true;
     }
     return false;
}

int Kalaha::numberPlayers()
{
    return 2;
}

std::vector<double> Kalaha::getPlayerScore(Field *field, int color, Position position) // parameter (bool) gameStopped for all getPlayerScores
{
    std::vector<double> playerScore;
    playerScore.push_back(field->get(0, 6) / field->get(1, 6));
    playerScore.push_back(field->get(1, 6) / field->get(0, 6));
/*
    if (gameStopped(field, )){
        Signal = "game_is_over";
    }
    else{
        Signal = "game_not_over";
    }
    */
    return playerScore;
}

