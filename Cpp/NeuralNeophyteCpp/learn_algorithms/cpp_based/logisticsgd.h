#ifndef LOGISTICSGD_H
#define LOGISTICSGD_H

#include "../../field.h"
class LogisticSgd
{
public:
    LogisticSgd();
    void fit(int learning_rate = 0.13, int n_epochs=1000);
    std::vector<int> predict(std::vector<int> field, int player);
};

#endif // LOGISTICSGD_H
