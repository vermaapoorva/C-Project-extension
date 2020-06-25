#include "defs.h"
#include "utils.h"

int max(int a, int b) { return (a > b ? a : b); }

int min(int a, int b) { return (a < b ? a : b); }

double generate_random_double(double max_value) {
  return max_value * ((double) rand() / RAND_MAX);
}

int get_ball_centre_y(void) {
  return ball.y + (ball.height / 2);
}

int get_paddle_centre_y(uint8_t paddle_no) {
  return paddles[paddle_no]->y + (paddles[paddle_no]->height / 2);
}

bool check_collision(ball_t ball, uint8_t paddle_no) {

  //Calculate the sides of the ball
  int left_ball = ball.x;
  int right_ball = ball.x + ball.width;
  int top_ball = ball.y;
  int bottom_ball = ball.y + ball.height;

  //Calculate the sides of the paddle
  SDL_Rect paddle = {
      paddles[paddle_no]->x,
      paddles[paddle_no]->y,
      paddles[paddle_no]->width,
      paddles[paddle_no]->height
  };
  int left_paddle = paddle.x;
  int right_paddle = paddle.x + paddle.w;
  int top_paddle = paddle.y;
  int bottom_paddle = paddle.y + paddle.h;

  if (top_ball >= bottom_paddle) {
    return 0;
  }
  if (bottom_ball <= top_paddle) {
    return 0;
  }
  if (left_ball > right_paddle) {
    return 0;
  }
  if (right_ball < left_paddle) {
    return 0;
  }

  return 1;

}
