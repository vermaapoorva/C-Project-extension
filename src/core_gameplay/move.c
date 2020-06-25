#include "../misc/defs.h"
#include "../misc/utils.h"
#include "../objects/init.h"
#include "move.h"

int PADDLE_DELTA = RELATIVE_PADDLE_SPEED *
                   (SCREEN_HEIGHT / FRAME_RATE);

bool move_paddle(uint8_t paddle_no, bool move, bool move_up) {
  // (bool) move determines if the paddle should move at all
  // (bool) move_up determines the direction of movement (1 up, 0 down)
  if (paddle_no > 1) {
    return false;
  }

  int this_y = paddles[paddle_no]->y;

  if (move) {
    if (move_up) {
      this_y = max(this_y - PADDLE_DELTA, 0);
    } else {
      this_y = min(this_y + PADDLE_DELTA,
                   SCREEN_HEIGHT - paddles[paddle_no]->height);
    }
  }

  paddles[paddle_no]->y = this_y;

  return true;
}


void ai_move_paddle(void) {
  int paddle_height_portion = paddles[AI_PADDLE]->height / 4;

  if (ball.x_velocity < 0) {
    int target_y = get_ball_centre_y();

    if ((target_y - get_paddle_centre_y(AI_PADDLE)) <
        -paddle_height_portion) {
      move_paddle(AI_PADDLE, true, true);
    } else if ((target_y - get_paddle_centre_y(AI_PADDLE)) >
               paddle_height_portion) {
      move_paddle(AI_PADDLE, true, false);
    }
  } else {
    int target_y = (SCREEN_HEIGHT / 2);

    if ((target_y - get_paddle_centre_y(AI_PADDLE)) <
        -paddle_height_portion) {
      move_paddle(AI_PADDLE, true, true);
    } else if ((target_y - get_paddle_centre_y(AI_PADDLE)) >
               paddle_height_portion) {
      move_paddle(AI_PADDLE, true, false);
    }
  }
}


void move_ball(void) {
  ball.x += ball.x_velocity;
  ball.y += ball.y_velocity;

  if ((ball.y < 0) || (ball.y > SCREEN_HEIGHT - ball.height)) {
    ball.y_velocity = -ball.y_velocity;
  }

  if (ball.x < 0) {

    score[1] += 1;
    init_paddles();
    init_ball();
    return;
  }

  if (ball.x > SCREEN_WIDTH - ball.width) {

    score[0] += 1;
    init_paddles();
    init_ball();
    return;
  }


  for (int i = 0; i < 2; i++) {

    if (check_collision(ball, i)) {
      float ball_y_delta = ((get_paddle_centre_y(i) - get_ball_centre_y())
                            / (paddles[i]->height / 2))
                           * generate_random_double(BALL_Y_MAX);

      //speeds up ball after each collision, if it slower than max speed
      if (abs(ball.x_velocity) < MAX_SPEED) {
        if (ball.x_velocity < 0) {
          //ball.y_velocity += ball_y_delta;
          ball.x_velocity -= 1;
        } else {
          ball.x_velocity += 1;
          //ball.y_velocity -= ball_y_delta;
        }
      }

      //change ball direction
      ball.x_velocity = -ball.x_velocity;
      ball.y_velocity += ball_y_delta;

      if (abs(ball.y_velocity) > BALL_Y_MAX) {
        ball.y_velocity = ((ball.y_velocity < 0) ? -BALL_Y_MAX : BALL_Y_MAX);
      }

      Mix_PlayChannel(-1, collision, 0);
    }
  }
}
