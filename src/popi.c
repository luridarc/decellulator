
#include "popi.h"

#define WIDTH 8
#define HEIGHT 7
#define CELLS_SIZE WIDTH * HEIGHT

enum state { EMPTY = 0, ALPHA, BETA, GAMMA, DELTA, EPSILON };

static enum state cells[CELLS_SIZE];
static int cells_colors[CELLS_SIZE * 3];

static void initCells() {
    for(int i = 0; i < CELLS_SIZE; i++) {
        cells[i] = EMPTY;
    }
}

static void initCellColors() {
    for(int i = 0; i < (CELLS_SIZE * 3); i++) {
        cells_colors[i] = 0;
    }
}

static char *getColorString(enum state s) {
    switch(s) {
        case ALPHA:
            return COLOR_ALPHA;
        case BETA:
            return COLOR_BETA;
        case GAMMA:
            return COLOR_GAMMA;
        case DELTA:
            return COLOR_DELTA;
        case EPSILON:
            return COLOR_EPSILON;
        default:
            return COLOR_NONE;
    }
}

static void setCellColor(int i, enum state s) {
    char *str = getColorString(s);

    sscanf(str, "%02x%02x%02x", 
        cells_colors + (i * 3) + 0,
        cells_colors + (i * 3) + 1,
        cells_colors + (i * 3) + 2
    );
}

static void updateCellColors() {
    for(int i = 0; i < CELLS_SIZE; i++) {
        setCellColor(i, cells[i]);
    }
}

void popi_newGame() {
    initCells();
    initCellColors();
}

int popi_selectCell(int x, int y) {

    updateCellColors();

    return 0;
}

int popi_gameOver() {
    return 0;
}

int popi_getCellsCount() {
    return CELLS_SIZE;
}

unsigned char popi_getRed(int i) {
    return cells_colors[(i * 3) + 0];
}

unsigned char popi_getGreen(int i) {
    return cells_colors[(i * 3) + 1];
}

unsigned char popi_getBlue(int i) {
    return cells_colors[(i * 3) + 2];
}

int popi_hasUpdated() {
    return 1;
}