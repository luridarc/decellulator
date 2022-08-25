
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 7

#include "board_cell.h"

class Board {
private:

    class Grid {
    public:
        // The board itself, a grid of boardcell objects
        static BoardCell data[BOARD_WIDTH * BOARD_HEIGHT];  

        static void generate();
    };

    class Islands {
    public:
        class Current {
        public:
            // This static int array should be cleared and reused for every
            // island evaluated, as only one island is really important at any
            // given time.
            static uint8_t data[56];

            static void clear();
            static void generate(uint8_t x, uint8_t y);
            static uint8_t size();
            static uint8_t rootIndex();
        };

        class List {
        public:
            // A list if 56 elements, 1 or 0. 1 signifying that a root cell
            // for an island exists at that index, and 0 meaning the opposite.
            static uint8_t data[56];

            static void clear();
            static void update();
            static uint8_t size();

            // generates a new island by finding a pair of elements and adding
            // a third.
            static void falsify();

            // get island given the coords. the island prointer returned points
            // to the static curren_island array within this class.
            static uint8_t * get(uint8_t x, uint8_t y);
        };
    };

    Board();
};