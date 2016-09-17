#ifndef RANDOMTEST_H
#define RANDOMTEST_H

#include <random>

class RandomTest
{
public:
    RandomTest();
    float getRandom();
private:
    std::random_device seed;
    std::mt19937 _rd;
};

#endif // RANDOMTEST_H
