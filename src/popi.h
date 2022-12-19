
#ifndef POPI
#define POPI

#define COLOR_NONE "000000"
#define COLOR_ALPHA "0000ff"
#define COLOR_BETA "00ff00"
#define COLOR_GAMMA "ff0000"
#define COLOR_DELTA "ff00ff"
#define COLOR_EPSILON "00ffff"

extern void popi_newGame();

extern int popi_getCells();
extern int popi_getCellsCount();

extern int popi_selectCell(int x, int y);

/**
 * Checks if game is complete and needs to be
 * reset with newGame()
 *
 * @return 0 or 1, false or true respectively
 */
extern int popi_gameOver();

extern int popi_hasUpdated();

#endif