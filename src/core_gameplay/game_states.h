#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "../misc/defs.h"

game_state main_menu(void);

game_state in_game(int mode, difficulty ai_difficulty);

difficulty select_difficulty(void);

#endif
