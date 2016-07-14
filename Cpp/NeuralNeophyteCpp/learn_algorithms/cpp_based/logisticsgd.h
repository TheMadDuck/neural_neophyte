#ifndef LOGISTICSGD_H
#define LOGISTICSGD_H

#include "../../field.h"
class LogisticSgd
{
public:
    LogisticSgd();
    void fit();
    std::vector<int> predict(std::vector<int> field, int player);
};

#endif // LOGISTICSGD_H
