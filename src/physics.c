#include "physics.h"

void update_ball_direction(GameState *state) {
    if (is_left_paddle_hit(state)) {
        state->ball_dx = 1;
    } else if (is_right_paddle_hit(state)) {
        state->ball_dx = -1;
    }

    if (is_top_or_bottom_hit(state->ball_y)) {
        state->ball_dy = -state->ball_dy;
    }
}

void move_ball(GameState *state) {
    state->ball_x += state->ball_dx;
    state->ball_y += state->ball_dy;
}

int is_inside_paddle(int y, int paddle_y) {
    return y >= paddle_y - 1 && y <= paddle_y + 1;
}

int is_top_or_bottom_hit(int ball_y) {
    return ball_y <= 1 || ball_y >= HEIGHT - 2;
}

int is_left_paddle_hit(const GameState *state) {
    return state->ball_x == LEFT_PADDLE_X + 1 &&
           is_inside_paddle(state->ball_y, state->left_paddle_y);
}

int is_right_paddle_hit(const GameState *state) {
    return state->ball_x == RIGHT_PADDLE_X - 1 &&
           is_inside_paddle(state->ball_y, state->right_paddle_y);
}
