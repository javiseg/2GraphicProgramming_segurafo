#include "Singleton.h"

Singleton* Singleton::instance = 0;

Singleton* Singleton::getInstance()
{
    if (instance == 0)
    {
        instance = new Singleton();
    }

    return instance;
}

Singleton::Singleton()
{
    FarDistance = 4000.0f;
    DirectionalIntensity = 0.4f;
    NumTexturas = 0;
    patrol_position = Vector3(0.0f, 5.0f, 0.0f);
    left_move = false;
    up_move = false;
}