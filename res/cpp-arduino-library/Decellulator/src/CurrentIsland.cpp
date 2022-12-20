
#include <CurrentIsland.h>

#include <Arduino.h>
#include <Grid.h>

void CurrentIsland::clear() {
    for(int i = 0; i < BOARD_LENGTH; i++) {
        data[i] = 0;
    }
}

uint8_t CurrentIsland::size() {
    uint8_t count = 0;
    for(int i = 0; i < BOARD_LENGTH; i++) {
        if(data[i] == 1) {
            count++;
        }
    }
    return count;
}

void CurrentIsland::generate(uint8_t x, uint8_t y) {
    clear();
    data[(y * BOARD_WIDTH) + y] = 1;
    expandIsland(x, y);
}

void CurrentIsland::expandIsland(uint8_t x, uint8_t y) {
    Cell::CellState root_value = Grid::get(x, y).value;
    searchRight(x, y, root_value);
    searchLeft(x, y, root_value);
    searchTop(x, y, root_value);
    searchBottom(x, y, root_value);
}

void CurrentIsland::searchRight(uint8_t x, uint8_t y, Cell::CellState root_value) {
    if(x + 1 < BOARD_WIDTH) {
        searchFromRoot(x + 1, y, root_value);
    }
}

void CurrentIsland::searchLeft(uint8_t x, uint8_t y, Cell::CellState root_value) {
    if(static_cast<int8_t>(x) - 1 >= 0) {
        searchFromRoot(x, y - 1, root_value);
    }
}

void CurrentIsland::searchTop(uint8_t x, uint8_t y, Cell::CellState root_value) {
    if(y + 1 < BOARD_WIDTH) {
        searchFromRoot(x, y + 1, root_value);
    }
}

void CurrentIsland::searchBottom(uint8_t x, uint8_t y, Cell::CellState root_value) {
    if(static_cast<int8_t>(y) - 1 >= 0) {
        searchFromRoot(x, y - 1, root_value);
    }
}

void CurrentIsland::searchFromRoot(uint8_t x, uint8_t y, Cell::CellState root_value) {
    if(data[(y * BOARD_WIDTH) + x] == 0){
        Cell::CellState test_value = Grid::get(x, y).value;
        if(root_value == test_value) {
            data[(y * BOARD_WIDTH) + x] = 1;
            expandIsland(x, y);
        }
    }
}

uint8_t CurrentIsland::getLeftBound() {
    uint8_t min = BOARD_WIDTH;

    for(uint8_t y = 0; y < BOARD_HEIGHT; y++) {
        for(uint8_t x = 0; x < BOARD_WIDTH; x++) {
            if(data[(y * BOARD_WIDTH) + x] == 1) {
                if(x < min) {
                    min = x;
                } 
            }
        }
    }

    return min;
}

uint8_t CurrentIsland::getRightBound() {
    uint8_t max = 0;

    for(uint8_t y = 0; y < BOARD_HEIGHT; y++) {
        for(uint8_t x = 0; x < BOARD_WIDTH; x++) {
            if(data[(y * BOARD_WIDTH) + x] == 1) {
                if(x > max) {
                    max = x;
                } 
            }
        }
    }

    return max;
}

uint8_t CurrentIsland::getTopColumnBound(uint8_t x) {
    uint8_t min = BOARD_HEIGHT;

    for(uint8_t y = 0; y < BOARD_HEIGHT; y++) {
        if(data[(y * BOARD_WIDTH) + x] == 1) {
            if(y < min) {
                min = y;
            } 
        }
    }

    return min;
}

uint8_t CurrentIsland::getBottomColumnBound(uint8_t x) {
    uint8_t max = 0;

    for(uint8_t y = 0; y < BOARD_HEIGHT; y++) {
        if(data[(y * BOARD_WIDTH) + x] == 1) {
            if(y > max) {
                max = y;
            } 
        }
    }

    return max;
}