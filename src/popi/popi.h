
#ifndef POPI_H
#define POPI_H

#define CELLS_WIDTH 8
#define CELLS_HEIGHT 7

#define COLOR_ERROR "000000"
#define COLOR_ALPHA "0000ff"
#define COLOR_BETA "00ff00"
#define COLOR_GAMMA "ff0000"
#define COLOR_DELTA "ff00ff"
#define COLOR_EPSILON "00ffff"

struct CellColor {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

extern void popi_newGame();
extern int popi_getCells();
extern int popi_getCellsCount();
extern void popi_selectCell(int x, int y);

/**
 * Checks if game is complete and needs to be
 * reset with newGame()
 *
 * @return 0 or 1, false or true respectively
 */
extern int popi_gameOver();
extern int popi_hasUpdated();
extern struct CellColor *popi_getCellColor(int x, int y);
char *popi_getCellColorString(int x, int y);
char popi_getCellChar(int x, int y);

#endif