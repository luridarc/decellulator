#include <stdlib.h>

#include "popi.h"

#define CELLS_SIZE CELLS_WIDTH * CELLS_HEIGHT

/**
 * @returns double between 0 and 1 (not inclusive)
 */
static double getRandom() {
    return (double)rand() / (double)((unsigned)RAND_MAX + 1);
}

//== STATES ===================================================================

static enum state { ERROR = -1, ALPHA, BETA, GAMMA, DELTA, EPSILON };

static enum state randomState() {
    return (unsigned char) ((getRandom() * 5));
}

/**
 * @param s State to be converted to string
 */
static char *stateToColorString(enum state s) {
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
        case ERROR:
            return COLOR_ERROR;
        default:
            return COLOR_ERROR;
    }
}

//== CELLS ====================================================================

static enum state cells[CELLS_SIZE];

static int coordsToCellsIndex(int x, int y) {
    if((x < 0) || (x >= CELLS_WIDTH)) return -1;
    if((y < 0) || (y >= CELLS_HEIGHT)) return -1;

    return (y * CELLS_WIDTH) + x;
}

static enum state getCell(int i) {
    if((i < 0) || (i >= CELLS_SIZE)) return ERROR;
    return cells[i];
}

static int setCell(int i, enum state s) {
    if((i < 0) || (i >= CELLS_SIZE)) return -1;
    cells[i] = s;
    return 0;
}

static int setCellWithCoords(int x, int y, enum state s) {
    return setCell(coordsToCellsIndex(x, y), s);
}

/**
 * Sets all cells to an initial random state
 */
static void initCells() {
    for(int i = 0; i < CELLS_SIZE; i++) {
        setCell(i, randomState());
    }
}

//=== CELL COLORS =============================================================

static unsigned char cells_colors[CELLS_SIZE * 3];

/**
 * @param i Index of cell in cells[]
 */
static void setCellColor(int i) {
    char *str = stateToColorString(getCell(i));

    sscanf(str, "%02x%02x%02x", 
        cells_colors + (i * 3) + 0,
        cells_colors + (i * 3) + 1,
        cells_colors + (i * 3) + 2
    );
}

/**
 * Iterate across all cells and set their color.
 */
static void updateCellColors() {
    for(int i = 0; i < CELLS_SIZE; i++) {
        setCellColor(i);
    }
}

//== CELL COLOR RETURNABLE ====================================================

static struct CellColor color;

/**
 * @param i Index of rgb state color in cells_colors[] to be set to color.
 */
static void setColor(int i) {
    color.red = cells_colors[(i * 3) + 0];
    color.green = cells_colors[(i * 3) + 1];
    color.blue = cells_colors[(i * 3) + 2];
}

static void clearColor() {
    color.red = 0;
    color.green = 0;
    color.blue = 0;
}

struct CellColor *popi_getCellColor(int x, int y) {
    int i = coordsToCellsIndex(x, y);

    if(i == -1) {
        clearColor();
    } else {
        setColor(i);
    }

    return &color;
}

//== CELL COLOR STRING ========================================================

static const char s_color[14];

static int setColorString(int i) {
    if(i >= CELLS_SIZE) return 1;

    color.red = cells_colors[(i * 3) + 0];
    color.green = cells_colors[(i * 3) + 1];
    color.blue = cells_colors[(i * 3) + 2];
    sprintf(s_color, "%d %d %d", color.red, color.green, color.blue);

    return 0;
}

static void clearColorString() {
    sprintf(s_color, "---, ---, ---");
}

char *popi_getCellColorString(int x, int y) {
    int i = coordsToCellsIndex(x, y);

    if(i == -1) {
        clearColorString();
    } else {
        if(!setColorString(i)) clearColorString();
    }

    return s_color;
}

//== CELL STATE CHAR ==========================================================

static unsigned char charFromState(int i) {
    if(i >= CELLS_SIZE) return ' ';
    
    switch(cells[i]) {
        case ERROR:
            return '#';
        case ALPHA:
            return 'A';
        case BETA:
            return 'B';
        case GAMMA:
            return 'G';
        case DELTA:
            return 'D';
        case EPSILON:
            return 'E';
        default:
            return '?';
    }
}

char popi_getCellChar(int x, int y) {
    int i = coordsToCellsIndex(x, y);

    if(i == -1) return ' ';

    return charFromState(i);
}

//=================

static enum state islands[CELLS_SIZE];
static enum state current_island[CELLS_SIZE];

//== GAME LOGIC ===============================================================

static int has_update = 0;

void popi_newGame() {
    initCells();
    updateCellColors();
}

void popi_selectCell(int x, int y) {
    
    setCellWithCoords(x, y, ERROR);

    has_update = 1;

    updateCellColors();
}

int popi_gameOver() {
    return 0;
}

int popi_getCellsCount() {
    return CELLS_SIZE;
}

int popi_hasUpdated() {
    return has_update;
}