#ifndef NRANDOMDISTRIB_H
#define NRANDOMDISTRIB_H
#include <chrono>
#include <random>

class NRandomDistrib
{
public:
    NRandomDistrib();
    int nRand(int border);
    int getRandomInt(int lowerBound, int upperBound);
private:
    std::mt19937 _rd;
};

#endif // NRANDOMDISTRIB_H
