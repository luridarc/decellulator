
#include <cstdint>

#include "board.h"

//=======================================================================
// BOARD
//=======================================================================

Board::Board() {
    Grid::generate();
    Islands::List::update();
}

//=======================================================================
// BOARD GRID
//=======================================================================

void Board::Grid::generate() {
    for(uint8_t y = 0; y < BOARD_HEIGHT; y++) {
        for(uint8_t x = 0; x < BOARD_WIDTH; x++) {
            data[(y * BOARD_WIDTH) + x] = BoardCell(x, y);
        }
    }
}

//=======================================================================
// BOARD ISLANDS LIST
//=======================================================================

void Board::Islands::List::clear() {
    for(auto i : data) { i = 0; }
}

void Board::Islands::List::update() {    
    List::clear();
    Current::clear();
    for(uint8_t y = 0; y < BOARD_HEIGHT; y++) {
        for(uint8_t x = 0; x < BOARD_WIDTH; x++) {
            Current::generate(x, y);

            if(Current::size() > 2) {
                const unsigned int index = Current::rootIndex();
                List::data[index] = 1;
            }
        }
    }

    if (List::size() == 0) {
        List::falsify();
        List::update();
    }
}

//=======================================================================
// BOARD ISLANDS CURRENT
//=======================================================================

void Board::Islands::Current::clear() {
    for(auto i : data) { i = 0; }
}

void Board::Islands::Current::generate(uint8_t x, uint8_t y) {
    
}