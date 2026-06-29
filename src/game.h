#ifndef GAME_H
#define GAME_H

#define WIDTH 80
#define HEIGHT 25
#define WIN_SCORE 21

#define LEFT_PADDLE_X 1
#define RIGHT_PADDLE_X (WIDTH - 2)

#define MIN_PADDLE_Y 2
#define MAX_PADDLE_Y (HEIGHT - 3)

#define NO_GOAL 0
#define LEFT_PLAYER_GOAL 1
#define RIGHT_PLAYER_GOAL 2

typedef enum {
    ACTION_NONE,
    ACTION_LEFT_UP,
    ACTION_LEFT_DOWN,
    ACTION_RIGHT_UP,
    ACTION_RIGHT_DOWN,
    ACTION_SKIP
} Action;

typedef struct {
    int left_paddle_y;
    int right_paddle_y;

    int ball_x;
    int ball_y;
    int ball_dx;
    int ball_dy;

    int left_score;
    int right_score;
} GameState;

void init_game(GameState *state);
void update_game(GameState *state, Action action);
int is_game_finished(const GameState *state);

int move_left_paddle(int current_y, Action action);
int move_right_paddle(int current_y, Action action);

int get_goal(int ball_x);
void apply_goal(GameState *state, int goal);
void reset_ball_after_goal(GameState *state, int goal);

#endif
