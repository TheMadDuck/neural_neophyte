#ifndef CHESS_H
#define CHESS_H
#include <string>
#include <vector>
#include "../field.h"

class Chess
{
public:
    //its just the four in a row template
    Chess();
    ~Chess();
    std::string getSignal();
    std::string getName();
    std::vector<int> getLegalInputs();
    Field* initField(int height = 6, int width = 7);
    bool isLegalMove(Field *field, int playerNumber, int position);
    void setStone(Field *field, int color, std::vector<int> position);
    bool gameStopped(Field *field, int roundNumber);
    int hasAWinner(Field *field, int color, int position);

private:
    std::string Signal = "";
    Field* _field;
};

#endif // CHESS_H
