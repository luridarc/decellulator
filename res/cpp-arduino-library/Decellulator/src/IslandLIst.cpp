
#include <IslandList.h>
#include <CurrentIsland.h>
#include <Grid.h>

void IslandList::clear() {
    for(int i = 0; i < BOARD_LENGTH; i++) {
        data[i] = 0;
    }
}

void IslandList::update() {
    clear();
    CurrentIsland::clear();
    for(uint8_t y = 0; y < BOARD_HEIGHT; y++) {
        for(uint8_t x = 0; x < BOARD_WIDTH; x++) {
            CurrentIsland::generate(x, y);

            if(CurrentIsland::size() > 2) {
                // if the island is larger than 2 elements
                // copy the values of that currentisland to
                // the island list
                for(int i = 0; i < BOARD_LENGTH; i++) {
                    if(CurrentIsland::data[i] == 1) {
                        data[i] = 1;
                    }
                }
            }
        }
    }

    if (size() == 0) {
        falsify();
        update();
    }
}

uint8_t IslandList::size() {
    int count = 0;
    for(int i = 0; i < BOARD_LENGTH; i++) {
        if(data[i] == 1) {
            count++;
        }
    }

    return count;
}

void IslandList::falsify() {
    for(int y = (BOARD_HEIGHT - 1); y >= 0; y--) {
        for(int x = 0; x < BOARD_WIDTH; x++) {
            Cell current_cell = Grid::get(x, y);

            if (Grid::lookNear(current_cell)) {
                Grid::set(x + 1, y, Cell(x + 1, y, current_cell.value));
            } else if (Grid::lookFar(current_cell)) {
                Grid::set(x + 2, y, Cell(x + 2, y, current_cell.value));
            }
        }
    }
}

uint8_t * IslandList::get(uint8_t x, uint8_t y) {
    if(data[(y * BOARD_WIDTH) + x] == 1) {
        CurrentIsland::clear();
        CurrentIsland::generate(x, y);
        return CurrentIsland::data;
    } else {
        return NULL;
    }
}