#pragma once
#include <iostream>
#include <math/vector_3.h>
class Singleton
{
private:
    /* Here will be the instance stored. */
    static Singleton* instance;

    /* Private constructor to prevent instancing. */
    Singleton();

public:
    /* Static access method. */
    static Singleton* getInstance();

    float FarDistance;
    float DirectionalIntensity;

    Vector3 patrol_position;
    bool left_move;
    bool up_move;
    int NumTexturas;
};
