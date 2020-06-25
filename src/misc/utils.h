#ifndef UTILS_H
#define UTILS_H

int get_paddle_centre_y(uint8_t paddle_no);

int max(int a, int b);

int min(int a, int b);

double generate_random_double(double max_value);

int get_ball_centre_y(void);

int get_paddle_centre_y(uint8_t paddle_no);

bool check_collision(ball_t ball, uint8_t paddle_no);

#endif