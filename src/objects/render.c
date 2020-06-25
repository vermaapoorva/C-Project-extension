#include "../misc/defs.h"
#include "render.h"

bool render_paddle(uint8_t paddle_no) {
  if (paddle_no > 1) {
    return false;
  }

  // Create white filled rectangle
  SDL_Rect this_rect = {
      paddles[paddle_no]->x,
      paddles[paddle_no]->y,
      paddles[paddle_no]->width,
      paddles[paddle_no]->height
  };

  SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(g_renderer, &this_rect);

  return true;
}

void render_button(button_t this_button) {
  SDL_RenderCopy(g_renderer, this_button.button_texture, NULL,
                 &this_button.bounding_rect);
}

void render_line(void) {
  // Draw dotted line of width 4 in centre of screen
  for (int i = -2; i < 3; i++) {
    for (int j = 0; j < SCREEN_HEIGHT; j += 8) {
      for (int k = 0; k < 4; k++) {
        SDL_RenderDrawPoint(g_renderer, (SCREEN_WIDTH - i) / 2, j + k);
      }
    }
  }
}

void render_ball(void) {
  SDL_Rect this_rect = {
      ball.x,
      ball.y,
      ball.width,
      ball.height
  };

  SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(g_renderer, &this_rect);
}

void clear_screen(void) {
  // Set background colour
  SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);

  // Clear background to selected colour
  SDL_RenderClear(g_renderer);
}