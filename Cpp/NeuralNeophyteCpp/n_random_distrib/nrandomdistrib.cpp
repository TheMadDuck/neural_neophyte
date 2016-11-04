#include "nrandomdistrib.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
NRandomDistrib::NRandomDistrib()
{
    _rd.seed(std::time(NULL));
}

int NRandomDistrib::nRand(int border)
{
    /*
    if(border == 0){
        return 0;
    }


    std::random_device rd;
    std::mt19937 gen(rd());

    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d(5,2);

    std::map<int, int> hist;
    for(int n=0; n<10000; ++n) {
        ++hist[std::round(d(gen))];
    }
    for(auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    }
    */
    return -2;
}

int NRandomDistrib::getRandomInt(int lowerBound, int upperBound)
{
    std::uniform_int_distribution<int> randomMoveDistrib(lowerBound, upperBound);
    return randomMoveDistrib(_rd);
}
