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

#include "fourinarow.h"
#include <iostream>



///////////////////////////////////////////////
/// \brief FourInARow::FourInARow
///

FourInARow::FourInARow()
{
    //_field = nullptr;
}

FourInARow::~FourInARow()
{
    //delete _field;
}

std::string FourInARow::getSignal()
{
    return Signal;
}

std::string FourInARow::getName()
{
    return "four_in_a_row";
}

int FourInARow::positionVectorSize()
{
    return 1;
}

std::vector<Position> FourInARow::getLegalInputs(Field *field, int activePlayer)
{
    std::vector<Position> legal_inputs;// = {0, 1, 2, 3, 4, 5, 6}; /Todo: speed limitation?
    for (int i = 0; i< 7 ; i++){
        if(field->get(0, i) == 0){
            legal_inputs.push_back(Position({i}));
        }
    }
    Signal = "legal_inputs_initialized";
    return legal_inputs;
}

Field *FourInARow::initField(int height, int width)
{
    // Game Field is 6 high and 7 wide, but we need a bottom row,
    // so the stones dont fall through the game

    Field* field = new Field(height +1, width);

    for (int i = 0; i < height - 1; ++i) {
        for (int j = 0; j < width; ++j) {
            field->set(0,i,j);
        }
    }

    // fill the bottom line with threes.
    for (int j = 0; j < width; ++j) {
        field->set(3,height,j);
    }


    Signal = "field_initialized";
    return field;
}

void FourInARow::setStone(Field *field, int color, Position position)
{
    color += 1; // players start with 0. clear field is marked with 0, too. change that?
    for (int i = 0; i < field->getHeight(); ++i) {
        if(field->get(i,position[0]) != 0){   // replace position[0] with getX()?
            field->set(color, i-1, position[0]);
            break;
        }
    }
    Signal = "stone_is_set";
    /*return field; //realy????*/
}

bool FourInARow::gameStopped(Field *field, int roundNumber, std::vector<Position> legal_inputs, Position lastMove)
{
    Signal = "game_not_over";  // probably not needed
    if(roundNumber + 1 == (field->getSizeField())){
        std::cout << "you played a draw" << std::endl;
        Signal = "game_is_over";
//        Signal = "we_have_a_draw";
        return 1;
    }


    int color = roundNumber % numberPlayers();
    color += 1;


    int longestLine = 0;
    //check depth of the new stone
    int depth = 0;
    for (int i = 0; i < field->getHeight(); ++i) {
        if (field->get(i, lastMove[0]) == 0) {
            depth += 1;
        }
        else {
            break;
        }
    }
    //column check:
    for (int i = 0; i < field->getHeight(); ++i) {
        if (field->get(i, lastMove[0]) == 0) {
            continue; /*TODO: Testen*/
        }
        if (field->get(i, lastMove[0]) == color) {
            longestLine += 1;
        }
        else{
            break;
        }

    }
    if (longestLine >= 4) {
        Signal = "game_is_over";
        return 1;
    }

    //row check:
    longestLine = 0;
    for (int i = 0; i < field->getWidth(); ++i) {
        if(field->get(depth, i) == color){
            longestLine += 1;
        }
        else {
            longestLine = 0;
        }
        if (longestLine >= 4){
            Signal = "game_is_over";
            return 1;
        }
    }

    //diagonal check:
    int longestLineUp = 0;
    int longestLineDown = 0;
    int topLeftStart = depth - lastMove[0];
    int bottomLeftStart = depth + lastMove[0];
    for (int i = 0; i < field->getWidth(); ++i) {
        if ((topLeftStart >= 0) && (topLeftStart < field->getHeight())) {
            if (field->get(topLeftStart, i) == color){
                longestLineUp += 1;
            }
            else{
                longestLineUp = 0;
            }
            if (longestLineUp >= 4){
                Signal = "game_is_over";
                return 1;
            }
        }
        topLeftStart += 1;

        if((bottomLeftStart >= 0) && (bottomLeftStart < field->getHeight())){
            if (field->get(bottomLeftStart, i) == color) {
                longestLineDown += 1;
            }
            else{
                longestLineDown = 0;
            }
            if (longestLineDown >= 4) {
                Signal = "game_is_over";
                return 1;
            }
        }
        bottomLeftStart -= 1;
    }
    return 0;

}

int FourInARow::numberPlayers()
{
    return 2;
}

std::vector<double> FourInARow::getPlayerScore(Field *field, int color, Position lastMove)
{
    //Signal = "game_not_over"; // probably not needed
    color += 1;
    std::vector<double> playerScore;
    for(int i = 0; i < numberPlayers(); ++i){
        playerScore.push_back(0);
    }


    int longestLine = 0;
    //check depth of the new stone
    int depth = 0;
    for (int i = 0; i < field->getHeight(); ++i) {
        if (field->get(i, lastMove[0]) == 0) {
            depth += 1;
        }
        else {
            break;
        }
    }
    //column check:
    for (int i = 0; i < field->getHeight(); ++i) {
        if (field->get(i,lastMove[0]) == 0) {
            continue; /*TODO: Testen*/
        }
        if (field->get(i,lastMove[0]) == color) {
            longestLine += 1;
        }
        else{
            break;
        }

    }
    if (longestLine >= 4) {
        Signal = "score_is_set";
        playerScore[color-1] = 1; // 0 variable is for gameFinishedYet (make own type?)
        return playerScore;
    }

    //row check:
    longestLine = 0;
    for (int i = 0; i < field->getWidth(); ++i) {
        if(field->get(depth, i) == color){
            longestLine += 1;
        }
        else {
            longestLine = 0;
        }
        if (longestLine >= 4){
            Signal = "score_is_set";
            playerScore[color-1] = 1;
            return playerScore;
        }
    }

    //diagonal check:
    int longestLineUp = 0;
    int longestLineDown = 0;
    int topLeftStart = depth - lastMove[0];
    int bottomLeftStart = depth + lastMove[0];
    for (int i = 0; i < field->getWidth(); ++i) {
        if ((topLeftStart >= 0) && (topLeftStart < field->getHeight())) {
            if (field->get(topLeftStart, i) == color){
                longestLineUp += 1;
            }
            else{
                longestLineUp = 0;
            }
            if (longestLineUp >= 4){
                Signal = "score_is_set";
                playerScore[color-1] = 1;
                return playerScore;
            }
        }
        topLeftStart += 1;

        if((bottomLeftStart >= 0) && (bottomLeftStart < field->getHeight())){
            if (field->get(bottomLeftStart, i) == color) {
                longestLineDown += 1;
            }
            else{
                longestLineDown = 0;
            }
            if (longestLineDown >= 4) {
                Signal = "score_is_set";
                playerScore[color -1] = 1;
                return playerScore;
            }
        }
        bottomLeftStart -= 1;
    }
    return playerScore;
}





