
#ifndef GRID_H
#define GRID_H

#include <Dimensions.h>

#include <Cell.h>

struct Grid {
    static Cell data[BOARD_HEIGHT * BOARD_WIDTH];

    static void generate();
    static Cell get(uint8_t x, uint8_t y);
    static void set(uint8_t x, uint8_t y, Cell new_cell);
    static bool lookNear(Cell current_cell);
    static bool lookFar(Cell current_cell);
    static bool look(uint8_t x, uint8_t y, Cell::CellState value);
};

#endif