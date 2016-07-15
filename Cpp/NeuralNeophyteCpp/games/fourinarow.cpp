#include "fourinarow.h"
#include <iostream>



///////////////////////////////////////////////
/// \brief FourInARow::FourInARow
///

FourInARow::FourInARow()
{
}

std::string FourInARow::getSignal()
{
    return Signal;
}

std::string FourInARow::getName()
{
    return "four_in_a_row";
}

std::vector<int> FourInARow::getLegalInputs()
{
    std::vector<int> legal_inputs = {0, 1, 2, 3, 4, 5, 6};
    Signal = "legal_inputs_initialized";
    return legal_inputs;
}

Field *FourInARow::initField(int height, int width)
{
    // Game Field is 6 high and 7 wide, but we need a bottom row,
    // so the stones dont fall through the game

    Field *field = new Field(height +1, width);

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

bool FourInARow::isLegalMove(Field *field, int playerNumber, int position)
{
    // wrong player number -> False
    if((playerNumber != 1) && (playerNumber != 2)){
        std::cout << playerNumber << " is invalid player number" << std::endl;
        Signal = "unvalid_player";
        return false;
    }
    // wrong position -> False
    if ((position < 0) || (position > field->getWidth() -1)){
        std::cout << position << " is a unvalid position" << std::endl;
        Signal = "unvalid_position";
        return false;
    }
    // column is already full -> False
    if (field->get(0, position) != 0){
        Signal = "column_is_full";
        return false;
    }
    // else -> True
    Signal = "move_is_legal";
    return true;
}

void FourInARow::setstone(Field *field, int color, int position)
{
    for (int i = 0; i < field->getHeight(); ++i) {
        if(field->get(i,position) != 0){
            field->set(color, i-1, position);
            break;
        }
    }
    Signal = "stone_is_set";
    /*return field; //realy????*/
}

bool FourInARow::gameStopped(Field *field, int roundNumber)
{
    if(roundNumber >= (field->getSize())){
        std::cout << "you played a draw" << std::endl;
        Signal = "game_is_over";
        return 1;
    }
}

int FourInARow::hasAWinner(Field* field, int color, int position)
{
    int longestLine = 0;
    //check depth of the new stone
    int depth = 0;
    for (int i = 0; i < field->getHeight(); ++i) {
        if (field->get(i, position) == 0) {
            depth += 1;
        }
        else {
            break;
        }
    }
    //column check:
    for (int i = 0; i < field->getHeight(); ++i) {
        if (field->get(i,position) == 0) {
            continue; /*TODO: Testen*/
        }
        if (field->get(i,position) == color) {
            longestLine += 1;
        }
        else{
            break;
        }

    }
    if (longestLine >= 4) {
        Signal = "we_have_a_winner";
        return color;
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
            Signal = "we_have_a_winner";
            return color;
        }
    }

    //diagonal check:
    int longestLineUp = 0;
    int longestLineDown = 0;
    int topLeftStart = depth - position;
    int bottomLeftStart = depth + position;
    for (int i = 0; i < field->getWidth(); ++i) {
        if ((topLeftStart >= 0) && (topLeftStart < field->getHeight())) {
            if (field->get(topLeftStart, i) == color){
                longestLineUp += 1;
            }
            else{
                longestLineUp = 0;
            }
            if (longestLineUp >= 4){
                Signal = "we_have_a_winner";
                return color;
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
                Signal = "we_have_a_winner";
                return color;
            }
        }
        bottomLeftStart -= 1;
    }
    return 0;
}





