

#ifndef BOARD_CELL
#define BOARD_CELL

class BoardCell {

public:
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

    BoardCell();
    BoardCell(uint8_t x, uint8_t y);

private:
    void setColor();
};

#endif