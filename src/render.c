#include <stdio.h>

#include "render.h"
#include "physics.h"

void draw_game(const GameState *state) {
    int x;
    int y;

    print_empty_lines();

    printf("Player 1: %d | Player 2: %d\n",
           state->left_score,
           state->right_score);

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            print_cell(x, y, state);
        }

        printf("\n");
    }

    printf("Controls: A/Z - left, K/M - right, Space - skip\n");
}

void print_cell(int x, int y, const GameState *state) {
    if (y == 0 || y == HEIGHT - 1) {
        printf("-");
    } else if (x == 0 || x == WIDTH - 1) {
        printf("|");
    } else if (x == state->ball_x && y == state->ball_y) {
        printf("o");
    } else if (x == LEFT_PADDLE_X &&
               is_inside_paddle(y, state->left_paddle_y)) {
        printf("|");
    } else if (x == RIGHT_PADDLE_X &&
               is_inside_paddle(y, state->right_paddle_y)) {
        printf("|");
    } else {
        printf(" ");
    }
}

void print_empty_lines(void) {
    int i;

    for (i = 0; i < HEIGHT; i++) {
        printf("\n");
    }
}

void print_winner(const GameState *state) {
    if (state->left_score >= WIN_SCORE) {
        printf("Congratulations! Player 1 wins!\n");
    } else if (state->right_score >= WIN_SCORE) {
        printf("Congratulations! Player 2 wins!\n");
    }
}
