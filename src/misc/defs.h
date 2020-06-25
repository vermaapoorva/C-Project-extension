#ifndef DEF_H
#define DEF_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FRAME_RATE (60)

#define BALL_Y_MAX (20)
#define MAX_SPEED (30)
#define RELATIVE_PADDLE_SPEED (5)

#define BUTTON_PADDING (10)

// Aiming for 60 frames per second, (1000/60 == 16.666..)
#define MS_PER_FRAME (17)

#define AI_PADDLE (0)
#define MAX_SPEED (30)

#define MAX_SCORE (5)

// PATHS

#define BACKGROUND_MUSIC_PATH ("../media/audio/background_music.wav")
#define BUTTON_PRESS_PATH ("../media/audio/button_sound.wav")
#define COLLISION_SOUND_PATH ("../media/audio/collision.wav")

#define FONT_PATH ("../media/fonts/os.ttf")

typedef struct {
    uint16_t width;
    uint16_t height;
    uint16_t x;
    uint16_t y;
} paddle_t;

typedef struct ball_s {
    double x;
    double y;
    int width;
    int height;
    double x_velocity;
    double y_velocity;
} ball_t;

typedef struct {
    SDL_Texture *button_texture;
    SDL_Rect bounding_rect;
} button_t;

typedef enum {
    MENU,
    SINGLE_PLAYER,
    TWO_PLAYER,
    NONE
} game_state;

typedef enum {
    EASY = 30,
    MEDIUM = 15,
    IMPOSSIBLE = 1
} difficulty;

// The below variables are globally defined as we want to create
//  the game in a single file initially. We can change this later.

// Window we'll be rendering to
SDL_Window *g_window;

// Surface contained by the window
SDL_Surface *g_screen_surface;

// Window renderer
SDL_Renderer *g_renderer;

// Image to be loaded and show on the screen
SDL_Surface *test_image;

// Sprites
paddle_t *paddles[2];
ball_t ball;
int score[2];

// Main game font
TTF_Font *menu_title_font;

// Background music
Mix_Music *background_music;

// Sound effects
Mix_Chunk *button_press;
Mix_Chunk *collision;

// Buttons and other static text
button_t main_title;
button_t single_player;
button_t two_player;

button_t difficulty_title;
button_t easy_difficulty_button;
button_t medium_difficulty_button;
button_t impossible_difficulty_button;

button_t game_over_text;
button_t winning_player_text;
button_t continue_guide_text;

button_t score_text;

//TODO need to implement functionality first
button_t multiplayer_online;

#endif
