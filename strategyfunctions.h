#ifndef STRATEGYFUNCTIONS_H
#define STRATEGYFUNCTIONS_H

//This Class provides static methods to get lambdas to determin Game Strategy
//SequenceGenerator and ResultProcessor

#include <random>
#include <algorithm>
#include <vector>
using namespace std;

#include "gamecore.h"

class StrategyFunctions
{
public:
    StrategyFunctions(){}
    static GameRandomSequenceGenerator GetSequenceGenerator();
    static GameResultProcessor GetResultProcessor();
};

#endif // STRATEGYFUNCTIONS_H
