
#include <Board.h>
#include <Grid.h>
#include <IslandList.h>

void Board::init() {
    Grid::generate();
    IslandList::update();
}