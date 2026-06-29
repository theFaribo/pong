#include "game.h"
#include "physics.h"

void init_game(GameState *state) {
    state->left_paddle_y = HEIGHT / 2;
    state->right_paddle_y = HEIGHT / 2;

    state->ball_x = WIDTH / 2;
    state->ball_y = HEIGHT / 2;
    state->ball_dx = 1;
    state->ball_dy = 1;

    state->left_score = 0;
    state->right_score = 0;
}

void update_game(GameState *state, Action action) {
    int goal;

    state->left_paddle_y = move_left_paddle(state->left_paddle_y, action);
    state->right_paddle_y = move_right_paddle(state->right_paddle_y, action);

    update_ball_direction(state);
    move_ball(state);

    goal = get_goal(state->ball_x);

    if (goal != NO_GOAL) {
        apply_goal(state, goal);
        reset_ball_after_goal(state, goal);
    }
}

int is_game_finished(const GameState *state) {
    return state->left_score >= WIN_SCORE || state->right_score >= WIN_SCORE;
}

int move_left_paddle(int current_y, Action action) {
    int new_y = current_y;

    if (action == ACTION_LEFT_UP && current_y > MIN_PADDLE_Y) {
        new_y = current_y - 1;
    } else if (action == ACTION_LEFT_DOWN && current_y < MAX_PADDLE_Y) {
        new_y = current_y + 1;
    }

    return new_y;
}

int move_right_paddle(int current_y, Action action) {
    int new_y = current_y;

    if (action == ACTION_RIGHT_UP && current_y > MIN_PADDLE_Y) {
        new_y = current_y - 1;
    } else if (action == ACTION_RIGHT_DOWN && current_y < MAX_PADDLE_Y) {
        new_y = current_y + 1;
    }

    return new_y;
}

int get_goal(int ball_x) {
    int goal = NO_GOAL;

    if (ball_x <= 0) {
        goal = RIGHT_PLAYER_GOAL;
    } else if (ball_x >= WIDTH - 1) {
        goal = LEFT_PLAYER_GOAL;
    }

    return goal;
}

void apply_goal(GameState *state, int goal) {
    if (goal == LEFT_PLAYER_GOAL) {
        state->left_score++;
    } else if (goal == RIGHT_PLAYER_GOAL) {
        state->right_score++;
    }
}

void reset_ball_after_goal(GameState *state, int goal) {
    state->ball_x = WIDTH / 2;
    state->ball_y = HEIGHT / 2;

    if (goal == LEFT_PLAYER_GOAL) {
        state->ball_dx = -1;
        state->ball_dy = -1;
    } else if (goal == RIGHT_PLAYER_GOAL) {
        state->ball_dx = 1;
        state->ball_dy = 1;
    }
}
