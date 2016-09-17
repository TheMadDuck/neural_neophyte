#include "randomtest.h"
#include <iostream>
#include <chrono>
//#include <time.h>

RandomTest::RandomTest()
{
    unsigned t = static_cast<unsigned> (std::time(NULL));
    std::cout << t << std::endl;
    _rd.seed(t);
    std::cout << " it WORKS !!!";
}

float RandomTest::getRandom()
{
    std::uniform_real_distribution<float> randomDistrib(0,1);
    //std::uniform_int_distribution<int> randomDistrib(0, 1);
    return randomDistrib(_rd);
}

