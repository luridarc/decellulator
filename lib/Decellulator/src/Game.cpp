
#include <Game.h>

#include <Grid.h>
#include <IslandList.h>
#include <Player.h>
#include <CurrentIsland.h>

void Game::init() {
    Grid::generate();
    IslandList::update();
    Player::reset();

    time_update = millis();
    player_win_value = 1000;
}

void Game::incrementProgress(uint16_t amt) {
    if((progress_time + amt) > win_amount) {
        progress_time = win_amount;
    } else {
        progress_time += amt;
    }
}

void Game::decrementProgress(uint16_t amt) {
    if((static_cast<int32_t>(progress_time) - amt) < win_amount) {
        progress_time = win_amount;
    } else {
        progress_time -= amt;
    }
}

uint8_t * Game::get_game_board() {
    static uint8_t color_game_board[GAME_BOARD_SIZE];

    for(int i = 0; i < BOARD_LENGTH; i++) {
        for(int j = 0; i < 3; i++) {
            color_game_board[(i * 3) + j] = Grid::data[i].color[j];
        }
    }

    return color_game_board;
}

void Game::select(uint8_t x, uint8_t y) {
    
    // running the get operation loads the current island to CurrentIsland::data,
    // and returns a pointer to it
    uint8_t * selection = IslandList::get(x, y);

    // since the current island data is loaded, check to see if it has more than 2
    // elements
    if(CurrentIsland::size() > 2) {

        static uint8_t x_min = CurrentIsland::getLeftBound();
        static uint8_t x_max = CurrentIsland::getRightBound();

        for(uint8_t current_x = x_min; current_x < x_max; current_x++) {

            static uint8_t y_min = CurrentIsland::getBottomColumnBound(current_x);
            static uint8_t y_max = CurrentIsland::getTopColumnBound(current_x);

            static uint8_t y_difference = (y_max + 1) - y_min;

            for(int current_y = (y_max - 1); current_y >= 0; current_y--) {
                if((current_y - y_difference) >= 0) {
                    Grid::set(current_x, current_y, Grid::get(current_x, current_y - y_difference));
                } else {
                    Grid::set(current_x, current_y, Cell(current_x, current_y));
                }
            }
        }

        IslandList::update();
    }
}