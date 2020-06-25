#include <math.h>

#include "../misc/defs.h"
#include "init.h"

static SDL_Color White = {255, 255, 255};

void init_button(button_t *this_button, char *text, int x, int y,
                 int width, int height) {
  // Select Difficulty Title

  SDL_Surface *this_surface;
  SDL_Texture *this_texture;

  this_surface = TTF_RenderText_Solid(menu_title_font,
                                      text,
                                      White);

  if (!this_surface) {
    printf("Could not create \"%s\" surface: %s\n", text, TTF_GetError());
    exit(EXIT_FAILURE);
  }

  this_texture = SDL_CreateTextureFromSurface(g_renderer, this_surface);

  if (!this_texture) {
    printf("Could not create \"%s\" texture: %s\n", text, TTF_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Rect this_rect = {x, y, width, height};

  this_button->bounding_rect = this_rect;
  this_button->button_texture = this_texture;

  SDL_FreeSurface(this_surface);
}

void init_game_over_buttons(char *message) {
  init_button(&game_over_text, "GAME OVER!",
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 2) / 2),
              (SCREEN_HEIGHT / 12),
              (SCREEN_WIDTH / 2),
              (SCREEN_HEIGHT / 3)
  );
  init_button(&winning_player_text, message,
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 4) / 2),
              (SCREEN_HEIGHT / 12) + (SCREEN_HEIGHT / 3),
              (SCREEN_WIDTH / 4),
              (SCREEN_HEIGHT / 6)
  );
  init_button(&continue_guide_text, "Press space to continue",
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 3) / 2),
              SCREEN_HEIGHT - (SCREEN_HEIGHT / 3),
              (SCREEN_WIDTH / 3),
              (SCREEN_HEIGHT / 6));
}

void init_difficulty_buttons(void) {
  // Select Difficulty Title

  init_button(&difficulty_title, "SELECT DIFFICULTY:",
              (SCREEN_WIDTH / 2) - (3 * (SCREEN_WIDTH / 4) / 2),
              BUTTON_PADDING,
              3 * (SCREEN_WIDTH / 4),
              (SCREEN_HEIGHT / 3)
  );

  init_button(&easy_difficulty_button, "EASY",
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 6) / 2),
              (SCREEN_HEIGHT / 3) + BUTTON_PADDING,
              (SCREEN_WIDTH / 6),
              (SCREEN_HEIGHT / 6)
  );

  init_button(&medium_difficulty_button, "MEDIUM",
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 6) / 2),
              (SCREEN_HEIGHT / 6) + (SCREEN_HEIGHT / 3) + BUTTON_PADDING,
              (SCREEN_WIDTH / 6),
              (SCREEN_HEIGHT / 6)
  );

  init_button(&impossible_difficulty_button, "IMPOSSIBLE",
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 6) / 2),
              ((2 * SCREEN_HEIGHT) / 6) + (SCREEN_HEIGHT / 3) + BUTTON_PADDING,
              (SCREEN_WIDTH / 6),
              (SCREEN_HEIGHT / 6)
  );

}

void init_menu_buttons(void) {
  // Main Menu Title

  init_button(&main_title, "PONG",
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 2) / 2),
              10,
              (SCREEN_WIDTH / 2),
              (SCREEN_HEIGHT / 2)
  );
  // Main Menu Single Player Option

  init_button(&single_player, "SINGLE PLAYER",
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 3) / 2),
              (SCREEN_HEIGHT / 2) + BUTTON_PADDING,
              (SCREEN_WIDTH / 3),
              (SCREEN_HEIGHT / 6)
  );

  // Main Menu Two Player Option

  init_button(&two_player, "TWO PLAYER",
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 3) / 2),
              (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 6) + BUTTON_PADDING,
              (SCREEN_WIDTH / 3),
              (SCREEN_HEIGHT / 6)
  );
}

void init_in_game_buttons(uint8_t player_one_score, uint8_t player_two_score) {
  // Score Texture

  char this_score[10 + (2 * (int) log10(MAX_SCORE))];

  sprintf(this_score, "%d - %d", player_one_score, player_two_score);

  init_button(&score_text, this_score,
              (SCREEN_WIDTH / 2) - ((SCREEN_WIDTH / 8) / 2),
              BUTTON_PADDING,
              (SCREEN_WIDTH / 8),
              (SCREEN_HEIGHT / 12)
  );
}

void init_score(void) {
  score[0] = 0;
  score[1] = 0;
}

void init_paddles(void) {
  for (int i = 0; i < 2; i++) {
    paddles[i] = malloc(sizeof(paddle_t));

    if (!paddles[i]) {
      printf("Couldn't allocate memory for paddle DT\n");
      exit(EXIT_FAILURE);
    }
  }

  paddles[0]->width = SCREEN_WIDTH / 30;
  paddles[0]->height = SCREEN_HEIGHT / 7;
  paddles[0]->x = 10;
  paddles[0]->y = 10;

  paddles[1]->width = SCREEN_WIDTH / 30;
  paddles[1]->height = SCREEN_HEIGHT / 7;
  paddles[1]->x = SCREEN_WIDTH - (SCREEN_WIDTH / 30) - 10;
  paddles[1]->y = SCREEN_HEIGHT - (SCREEN_HEIGHT / 7) - 10;
}

void init_ball(void) {

  ball.x = (SCREEN_WIDTH / 2);
  ball.y = (SCREEN_HEIGHT / 2);
  ball.width = 10;
  ball.height = 10;
  ball.x_velocity = 2 * ((rand() & 1) ? -1 : 1);
  ball.y_velocity = ((double) rand() / RAND_MAX);
}

static void init_font(void) {
  menu_title_font = TTF_OpenFont(FONT_PATH, 30);

  if (!menu_title_font) {
    printf("Could not open menu font: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
}

static void init_audio(void) {
  // Initialize SDL_mixer
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("Could not initialise SDL_mixer: %s\n", Mix_GetError());
    exit(EXIT_FAILURE);
  }
  // Load music
  background_music = Mix_LoadMUS(BACKGROUND_MUSIC_PATH);
  if (!background_music) {
    printf("Could not load \"background_music\": %s\n", Mix_GetError());
    //exit(EXIT_FAILURE);
  }

  // Load sound effects
  button_press = Mix_LoadWAV(BUTTON_PRESS_PATH);
  if (!button_press) {
    printf("Could not load \"button_sound\" sound effect: %s\n",
           Mix_GetError());
    exit(EXIT_FAILURE);
  }

  collision = Mix_LoadWAV(COLLISION_SOUND_PATH);
  if (!collision) {
    printf("Could not load \"collision\" sound effect: %s\n", Mix_GetError());
    exit(EXIT_FAILURE);
  }

  if (!Mix_PlayingMusic() && background_music) {
    //Play the music
    Mix_PlayMusic(background_music, -1);
  }

}

// Starts SDL and loads window
static void init_window(void) {
  // Initialise SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("Could not initialise SDL: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create SDL Window
  g_window = SDL_CreateWindow("Pong",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);


  if (!g_window) {
    printf("Could not create window: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create renderer
  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

  if (!g_renderer) {
    printf("Could not create renderer: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Get window surface
  g_screen_surface = SDL_GetWindowSurface(g_window);
}

void init_game(void) {

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    printf("Could not initialise SDL_Image: %s\nEXITING\n", IMG_GetError());
  }

  if (TTF_Init() == -1) {
    printf("Could not initialise SDL_ttf: %s\nEXITING\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }

  init_window();
  init_audio();

  init_font();
  init_paddles();
  init_ball();
  init_score();
}
