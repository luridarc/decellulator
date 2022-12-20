
#include <Arduino.h>

#define GAME_BOARD_SIZE 56 * 3

class Game {
    static unsigned long progress_time;
    static unsigned long last_success_time;
    static unsigned long time_update;
    static uint16_t win_amount;
    static uint16_t player_win_value;
    static bool game_over;
    static bool helped;

public:
    static void init();
    static void incrementProgress(uint16_t amt);
    static void decrementProgress(uint16_t amt);
    static uint8_t * get_game_board();
    static void select(uint8_t x, uint8_t y);
};