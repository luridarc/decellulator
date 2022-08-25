
#include "board_cell.h"

#include <cstdlib>

BoardCell::BoardCell(uint8_t x, uint8_t y) {

    this->position[0] = x;
    this->position[1] = y;
    this->value = static_cast<CellState>(rand() % 5 + 1);;
    this->setColor();
}

void BoardCell::setColor() {
    switch(this->value){
        case CellState::ONE:
            this->color[0] = 255;
            this->color[1] = 0;
            this->color[2] = 0;
            break;
        case CellState::TWO:
            this->color[0] = 0;
            this->color[1] = 255;
            this->color[2] = 0;
            break;
        case CellState::THREE:
            this->color[0] = 0;
            this->color[1] = 0;
            this->color[2] = 255;
            break;
        case CellState::FOUR:
            this->color[0] = 0;
            this->color[1] = 255;
            this->color[2] = 255;
            break;
        case CellState::FIVE:
            this->color[0] = 255;
            this->color[1] = 0;
            this->color[2] = 255;
            break;
    }
}

