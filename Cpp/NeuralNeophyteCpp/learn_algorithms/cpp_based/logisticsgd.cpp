#include "logisticsgd.h"
#include <iostream>

LogisticSgd::LogisticSgd()
{
}

void LogisticSgd::fit(std::array<SaveList*, 3> dataset, int learning_rate, int n_epochs)
{
    SaveList* train_set_x = dataset[0];
}

std::vector<int> LogisticSgd::predict(std::vector<int> field, int player)
{
    std::vector<int> a{5,4,3};                    // TODO: IMPLEMENT!!!!!!!!!!!
    //std::cout << "NOT YET IMPLEMENTED!!!!!!!!" << std::endl;
    return a;
}
