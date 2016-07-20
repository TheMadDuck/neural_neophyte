#ifndef SAVELIST_H
#define SAVELIST_H

#include "field.h"
#include <vector>

class SaveList
{
public:
    SaveList();
    void savePositions(Field field, int color, int roundNumber, int position, bool transposed);

private:
//    std::vector<std::vector<int>> playerOne;
//    std::vector<std::vector<int>> playerTwo;

    std::vector<std::vector<int>> playerOneFields;
    std::vector<int> playerOnePositions;

    std::vector<std::vector<int>> playerTwoFields;
    std::vector<int> playerTwoPositions;

    //std::vector<> playerOne;

};

#endif // SAVELIST_H
