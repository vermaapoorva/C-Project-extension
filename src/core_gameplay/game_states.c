#include "game_states.h"
#include "../misc/defs.h"
#include "../objects/init.h"
#include "../objects/render.h"
#include "../objects/destroy.h"
#include "move.h"
#include "../misc/utils.h"
#include "assert.h"

static void game_over(uint8_t winning_player) {
  assert(winning_player == 0 || winning_player == 1);
  assert(score_text.button_texture != NULL);

  if (winning_player) {
    init_game_over_buttons("Player 2 wins!");
  } else {
    init_game_over_buttons("Player 1 wins!");
  }

  uint16_t last_tick_time = (uint16_t) SDL_GetTicks();
  uint16_t this_sleep = 0;

  bool quit = false;

  SDL_Event event;

  while (!quit) {

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        // If user clicks close button
        exit(EXIT_SUCCESS);
      } else if (event.type == SDL_KEYDOWN &&
                 event.key.keysym.sym == SDLK_SPACE) {
        quit = true;
        break;
      }
    }

    clear_screen();

    // RENDER MENU BUTTONS

    render_button(score_text);

    render_button(game_over_text);

    render_button(winning_player_text);

    render_button(continue_guide_text);

    this_sleep = SDL_GetTicks() - last_tick_time;
    // Delay added to maintain constant framerate
    if (this_sleep <= MS_PER_FRAME) {
      // Makes up difference with delay if time delta is less
      // than frame time, continues otherwise
      SDL_Delay(MS_PER_FRAME - this_sleep);
    }

    last_tick_time = SDL_GetTicks();

    SDL_RenderPresent(g_renderer);
  }

  clear_screen();

  free_game_over_buttons();
}

// Main menu
game_state main_menu(void) {

  init_menu_buttons();

  game_state state_to_go_to = NONE;

  uint16_t last_tick_time = (uint16_t) SDL_GetTicks();
  uint16_t this_sleep = 0;

  SDL_Rect coord_rect = {0, 0, 1, 1};

  bool quit = false;

  SDL_Event event;

  while (!quit) {

    while (SDL_PollEvent(&event)) {
      // Set to white
      SDL_SetTextureColorMod(single_player.button_texture, 255, 255, 255);
      SDL_SetTextureColorMod(two_player.button_texture, 255, 255, 255);

      if (event.type == SDL_QUIT) {
        // If user clicks close button
        exit(EXIT_SUCCESS);
      } else if (event.type == SDL_MOUSEMOTION
                 || event.type == SDL_MOUSEBUTTONDOWN
                 || event.type == SDL_MOUSEBUTTONUP) {
        SDL_GetMouseState(&coord_rect.x, &coord_rect.y);

        if (SDL_HasIntersection(&single_player.bounding_rect, &coord_rect)) {
          //Set to grey
          SDL_SetTextureColorMod(single_player.button_texture, 153, 149, 133);

          if (event.type == SDL_MOUSEBUTTONUP) {
            Mix_PlayChannel(-1, button_press, 0);
            quit = true;
            state_to_go_to = SINGLE_PLAYER;
          }
        }
        if (SDL_HasIntersection(&two_player.bounding_rect, &coord_rect)) {
          //Set to grey
          SDL_SetTextureColorMod(two_player.button_texture, 153, 149, 133);

          if (event.type == SDL_MOUSEBUTTONUP) {
            Mix_PlayChannel(-1, button_press, 0);
            quit = true;
            state_to_go_to = TWO_PLAYER;
          }
        }
      }
    }

    clear_screen();

    // RENDER MENU BUTTONS

    render_button(main_title);

    render_button(single_player);

    render_button(two_player);

    this_sleep = SDL_GetTicks() - last_tick_time;
    // Delay added to maintain constant framerate
    if (this_sleep <= MS_PER_FRAME) {
      // Makes up difference with delay if time delta is less
      // than frame time, continues otherwise
      SDL_Delay(MS_PER_FRAME - this_sleep);
    }

    last_tick_time = SDL_GetTicks();

    SDL_RenderPresent(g_renderer);
  }

  // Reset texture colours
  SDL_SetTextureColorMod(single_player.button_texture, 0xff, 0xff, 0xff);

  free_menu_buttons();
  return state_to_go_to;
}

// Main game loop
game_state in_game(int mode, difficulty ai_difficulty) {
  init_in_game_buttons(score[0], score[1]);
  init_score();

  game_state state_to_go_to = MENU;

  uint16_t last_tick_time = (uint16_t) SDL_GetTicks();
  uint16_t this_sleep = 0;
  int count = 0;

  bool quit = false;

  SDL_Event event;

  while (!quit) {
    switch (mode) {
      case (0):
        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            // If user clicks close button
            exit(EXIT_SUCCESS);
          } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
              case SDLK_UP:
                // Move right paddle up
                move_paddle(1, true, true);
                break;
              case SDLK_DOWN:
                // Move right paddle down
                move_paddle(1, true, false);
                break;
            }
          }
        }
        if (!(count % ai_difficulty)) {
          ai_move_paddle();
        }
        count++;
        break;
      case (1):
        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            // If user clicks close button
            exit(EXIT_SUCCESS);
          } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
              case SDLK_UP:
                // Move right paddle up
                move_paddle(1, true, true);
                break;
              case SDLK_DOWN:
                // Move right paddle down
                move_paddle(1, true, false);
                break;
              case SDLK_w:
                // Move left paddle up
                move_paddle(0, true, true);
                break;
              case SDLK_s:
                // Move left paddle down
                move_paddle(0, true, false);
                break;
            }
          }
        }
    }


    move_ball();

    if (score[0] == MAX_SCORE || score[1] == MAX_SCORE) {
      quit = true;
      state_to_go_to = MENU;
      init_in_game_buttons(score[0], score[1]);
      game_over(score[1] == MAX_SCORE);
      init_score();
      continue;
    }

    clear_screen();
    render_paddle(0);
    render_paddle(1);
    render_line();
    render_ball();

    init_in_game_buttons(score[0], score[1]);
    render_button(score_text);


    //check whether the ball is out of bounds, and update the scores, and restart the game

    this_sleep = SDL_GetTicks() - last_tick_time;
    // Delay added to maintain constant framerate
    if (this_sleep <= MS_PER_FRAME) {
      // Makes up difference with delay if time delta is less
      // than frame time, continues otherwise
      SDL_Delay(MS_PER_FRAME - this_sleep);
    }

    last_tick_time = SDL_GetTicks();

    SDL_RenderPresent(g_renderer);
  }

  free_in_game_buttons();
  return state_to_go_to;
}

difficulty select_difficulty(void) {
  init_difficulty_buttons();

  uint16_t last_tick_time = (uint16_t) SDL_GetTicks();
  uint16_t this_sleep = 0;

  difficulty ret_difficulty;

  SDL_Rect coord_rect = {0, 0, 1, 1};

  bool quit = false;

  SDL_Event event;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      SDL_SetTextureColorMod(easy_difficulty_button.button_texture, 255,
                             255, 255);
      SDL_SetTextureColorMod(medium_difficulty_button.button_texture, 255,
                             255, 255);
      SDL_SetTextureColorMod(impossible_difficulty_button.button_texture,
                             255, 255, 255);

      if (event.type == SDL_QUIT) {
        // If user clicks close button
        quit = true;
        exit(EXIT_SUCCESS);
      } else if (event.type == SDL_MOUSEMOTION
                 || event.type == SDL_MOUSEBUTTONDOWN
                 || event.type == SDL_MOUSEBUTTONUP) {
        SDL_GetMouseState(&coord_rect.x, &coord_rect.y);

        if (SDL_HasIntersection(&easy_difficulty_button.bounding_rect,
                                &coord_rect)) {
          //Set to grey
          SDL_SetTextureColorMod(easy_difficulty_button.button_texture, 153,
                                 149, 133);

          if (event.type == SDL_MOUSEBUTTONUP) {
            Mix_PlayChannel(-1, button_press, 0);
            quit = true;
            ret_difficulty = EASY;
          }
        } else if (SDL_HasIntersection(&medium_difficulty_button.bounding_rect,
                                       &coord_rect)) {
          //Set to grey
          SDL_SetTextureColorMod(medium_difficulty_button.button_texture, 153,
                                 149, 133);

          if (event.type == SDL_MOUSEBUTTONUP) {
            Mix_PlayChannel(-1, button_press, 0);
            quit = true;
            ret_difficulty = MEDIUM;
          }
        } else if (SDL_HasIntersection(
            &impossible_difficulty_button.bounding_rect, &coord_rect)) {
          //Set to grey
          SDL_SetTextureColorMod(impossible_difficulty_button.button_texture,
                                 153, 149, 133);

          if (event.type == SDL_MOUSEBUTTONUP) {
            Mix_PlayChannel(-1, button_press, 0);
            quit = true;
            ret_difficulty = IMPOSSIBLE;
          }
        } else {
          //Set to white
          SDL_SetTextureColorMod(easy_difficulty_button.button_texture, 255,
                                 255, 255);
          SDL_SetTextureColorMod(medium_difficulty_button.button_texture, 255,
                                 255, 255);
          SDL_SetTextureColorMod(impossible_difficulty_button.button_texture,
                                 255, 255, 255);
        }
      }
    }

    clear_screen();

    render_button(difficulty_title);
    render_button(easy_difficulty_button);
    render_button(medium_difficulty_button);
    render_button(impossible_difficulty_button);

    this_sleep = SDL_GetTicks() - last_tick_time;
    // Delay added to maintain constant framerate
    if (this_sleep <= MS_PER_FRAME) {
      // Makes up difference with delay if time delta is less
      // than frame time, continues otherwise
      SDL_Delay(MS_PER_FRAME - this_sleep);
    }

    last_tick_time = SDL_GetTicks();

    SDL_RenderPresent(g_renderer);
  }

  free_difficulty_buttons();

  return ret_difficulty;
}
