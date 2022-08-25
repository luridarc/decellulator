
#ifndef Cell_H
#define Cell_H

#include <Arduino.h>

struct Cell {
    enum CellState {
        ONE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE
    };

    CellState value;
    uint8_t position[2];
    uint8_t color[3];

    Cell();
    Cell(uint8_t x, uint8_t y);
    Cell(uint8_t x, uint8_t y, CellState value);
    
    void setColor();
    uint8_t * getColor();
};

#endif