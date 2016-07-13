#ifndef FOURINAROW_H
#define FOURINAROW_H
#include <string>
#include <vector>
#include <array>

class Field
{
public:
    Field(int height, int width); /*vieleicht noch ne init schreiben?*/
    int get(int i, int j);
    void set(int value, int i, int j);
    int getHeight();
    int getWidth();
    int getSize();
    void showField();

private:
    std::vector<std::vector<int>> _field;
    int _height;
    int _width;
};



class FourInARow
{
public:
    FourInARow();
    std::string getSignal();
    std::string getName();
    std::array<int, 7> getLegalInputs();
    Field* initField(int height = 6, int width = 7);
    bool isLegalMove(Field *field, int playerNumber, int position);
    void setstone(Field *field, int color, int position);
    bool gameStopped(Field *field, int roundNumber);
    int hasAWinner(Field *field, int color, int position); /*TODO: Testen*/

private:
    std::string Signal = "";
    //Field* field;
};

#endif // FOURINAROW_H
