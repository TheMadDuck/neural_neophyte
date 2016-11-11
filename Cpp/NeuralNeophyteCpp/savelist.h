#ifndef SAVELIST_H
#define SAVELIST_H

#include "field.h"
#include <vector>

class SaveList
{
public:
    SaveList();
    void savePositions(Field field, int color, int roundNumber, int position, bool transposed);
    int _test;

private:
    std::vector<std::vector<int>> _playerOneFields;
    std::vector<int> _playerOnePositions;

    std::vector<std::vector<int>> _playerTwoFields;
    std::vector<int> _playerTwoPositions;

};

#endif // SAVELIST_H
