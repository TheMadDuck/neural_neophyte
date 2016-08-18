#ifndef TRAINTESTVALIDATE_H
#define TRAINTESTVALIDATE_H
#include <iostream>
#include <array>
#include "gameflow.h"
#include "n_random_distrib/nrandomdistrib.h"

class TrainTestValidate
{
public:
    TrainTestValidate();
    std::array<SaveList*, 3> run(GameFlow* gameFlow, int numberTrain, int numberTest, int numberValidate, int numberModels);
private:
    NRandomDistrib _nRand;
};

#endif // TRAINTESTVALIDATE_H
