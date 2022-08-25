
#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>

struct Player {
    static uint16_t score;

    static void reset();
};

#endif