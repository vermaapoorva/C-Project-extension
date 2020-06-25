#include "../misc/defs.h"
#include "destroy.h"

void free_menu_buttons(void) {
  SDL_DestroyTexture(single_player.button_texture);
  SDL_DestroyTexture(main_title.button_texture);
}

void free_difficulty_buttons(void) {
  SDL_DestroyTexture(difficulty_title.button_texture);
  SDL_DestroyTexture(easy_difficulty_button.button_texture);
  SDL_DestroyTexture(medium_difficulty_button.button_texture);
  SDL_DestroyTexture(impossible_difficulty_button.button_texture);
}

void free_game_over_buttons(void) {
  SDL_DestroyTexture(game_over_text.button_texture);
  SDL_DestroyTexture(winning_player_text.button_texture);
  SDL_DestroyTexture(continue_guide_text.button_texture);
}

void free_in_game_buttons(void) {
  SDL_DestroyTexture(score_text.button_texture);
}

void free_font(void) {
  TTF_CloseFont(menu_title_font);
}

void free_paddles(void) {
  for (int i = 0; i < 2; i++) {
    free(paddles[i]);
  }
}

void free_audio(void) {
  Mix_HaltMusic();

  // Free background music
  Mix_FreeMusic(background_music);

  // Free sound effects
  Mix_FreeChunk(button_press);
  Mix_FreeChunk(collision);
}

// Frees window
void close_game(void) {
  free_paddles();
  free_font();

  // Closing TTF
  TTF_Quit();

  // Closing audio
  Mix_Quit();

  // Closing SDL
  SDL_DestroyRenderer(g_renderer);

  SDL_DestroyWindow(g_window);

  SDL_Quit();

  exit(EXIT_SUCCESS);
}