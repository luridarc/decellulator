
#ifndef CURRENTISLAND_H
#define CURRENTISLAND_H

#include <Dimensions.h>

#include <Cell.h>
#include <Arduino.h>

struct CurrentIsland {
    static uint8_t data[BOARD_LENGTH];

    static void clear();
    static void generate(uint8_t x, uint8_t y);
    static uint8_t size();
    static uint8_t getLeftBound();
    static uint8_t getRightBound();
    static uint8_t getBottomColumnBound(uint8_t current_x);
    static uint8_t getTopColumnBound(uint8_t current_x);

private:
    static void expandIsland(uint8_t x, uint8_t y);
    static void searchFromRoot(uint8_t x, uint8_t y, Cell::CellState root_value);
    static void searchRight(uint8_t x, uint8_t y, Cell::CellState root_value);
    static void searchLeft(uint8_t x, uint8_t y, Cell::CellState root_value);
    static void searchTop(uint8_t x, uint8_t y, Cell::CellState root_value);
    static void searchBottom(uint8_t x, uint8_t y, Cell::CellState root_value);
};

#endif