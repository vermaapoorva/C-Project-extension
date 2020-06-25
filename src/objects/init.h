#ifndef INIT_H
#define INIT_H

void init_button(button_t *this_button, char *text, int x, int y, int width,
                 int height);

void init_menu_buttons(void);

void init_game_over_buttons(char *message);

void init_difficulty_buttons(void);

void init_in_game_buttons(uint8_t player_one_score, uint8_t player_two_score);

void init_game(void);

void init_score(void);

void init_paddles(void);

void init_ball(void);

#endif