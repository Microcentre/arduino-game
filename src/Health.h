#ifndef HEALTH_H
#define HEALTH_H

#include "stdint.h"

class Health
{
public:
    Health();

    void adjust();

    void show();

    void (*resetFunc)(void) = 0;

private:
    const uint8_t GAME_OVER_HEALTH = 0;
    uint8_t health = 3;
};

#endif