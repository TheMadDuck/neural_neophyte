#ifndef FOURINAROW_H
#define FOURINAROW_H
#include <string>
#include <vector>
#include <array>
#include "../field.h"



class FourInARow
{
public:
    FourInARow();
    std::string getSignal();
    std::string getName();
    std::vector<int> getLegalInputs();
    Field* initField(int height = 6, int width = 7);
    bool isLegalMove(Field *field, int playerNumber, int position);
    void setStone(Field *field, int color, int position);
    bool gameStopped(Field *field, int roundNumber);
    int hasAWinner(Field *field, int color, int position); /*TODO: Testen*/

private:
    std::string Signal = "";
    //Field* field;
};

#endif // FOURINAROW_H
