#pragma once

#include <cstdlib>
#include <ctime>

class Random
{
private:
    static Random instance;

public:
    Random()
    {
        srand(time(0));
    }

    static Random &getInstance()
    {
        return instance;
    }

    int range(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }
};
Random Random::instance;

