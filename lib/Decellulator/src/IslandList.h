
#ifndef ISLANDLIST_H
#define ISLANDLIST_H

#include <Dimensions.h>

#include <Arduino.h>

/**
 * The island list is an array of 56 1's and 0's. 1's designate that the cell
 * is part of an island, and a 0 denotes the opposite. The idea here is that 
 * every time we need to get a specific island, first the selected coordinates
 * are checked against the data array to see if it is a 1. If it is, then it is
 * a part of an island. If it is indeed part of an island, then we can propogate 
 * that island in CurrentIsland::data and then return the pointer to that. 
 * 
 * This would be a poor way of doing if we had a lot of elements, as each propogation's way
 * of doing it is 56^2 I believe theoretically, though that wont ever get close to being
 * reached just due to the nature of the way the game works.
 */

struct IslandList {
    static uint8_t data[BOARD_LENGTH];

    static void clear();
    static void update();
    static uint8_t size();
    static void falsify();

    // get a specific island
    static uint8_t * get(uint8_t x, uint8_t y);
};

#endif