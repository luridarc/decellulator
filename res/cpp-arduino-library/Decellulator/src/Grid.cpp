
#include <Grid.h>

void Grid::generate() {
    for(uint8_t y = 0; y < BOARD_HEIGHT; y++) {
        for(uint8_t x = 0; x < BOARD_WIDTH; x++) {
            data[(y * BOARD_WIDTH) + x] = Cell(x, y);
        }
    }
}

Cell Grid::get(uint8_t x, uint8_t y) {
    return data[(y * BOARD_WIDTH) + x];
}

void Grid::set(uint8_t x, uint8_t y, Cell new_cell) {
    new_cell.position[0] = x;
    new_cell.position[1] = y;
    data[(y * BOARD_WIDTH) + x] = new_cell;
}

bool Grid::lookNear(Cell current_cell) {
    return look(
        current_cell.position[0] + 1,
        current_cell.position[1],
        current_cell.value
    );
}

bool Grid::lookFar(Cell current_cell) {
    return look(
        current_cell.position[0] + 2,
        current_cell.position[1],
        current_cell.value
    );
}

bool Grid::look(uint8_t x, uint8_t y, Cell::CellState current_value) {
    if(x < BOARD_WIDTH) {
        Cell::CellState forward_value = get(x, y).value;

        if(forward_value == current_value) {
            return true;
        }
    }

    return false;
}