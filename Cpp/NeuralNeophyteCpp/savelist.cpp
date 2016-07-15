#include "savelist.h"

SaveList::SaveList()
//:playerOneFields({{}}), playerTwo({{},{}})  //TODO: test obs immer normal initialisiert wird
{
}

void SaveList::savePositions(Field field, int color, int roundNumber, int position, bool transposed)
{
    std::vector<int> flatField = field.flatten();
    if (color == 1) {
        flatField.push_back(1);
        flatField.push_back(roundNumber);
        playerOneFields.push_back(flatField);
        playerOnePositions.push_back(position);
    }
    if (color == 2) {
        flatField.push_back(2);
        flatField.push_back(roundNumber);
        playerTwoFields.push_back(flatField);
        playerTwoPositions.push_back(position);
    }
}
