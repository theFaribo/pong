#ifndef PHYSICS_H
#define PHYSICS_H

#include "game.h"

void update_ball_direction(GameState *state);
void move_ball(GameState *state);

int is_inside_paddle(int y, int paddle_y);
int is_top_or_bottom_hit(int ball_y);
int is_left_paddle_hit(const GameState *state);
int is_right_paddle_hit(const GameState *state);

#endif
