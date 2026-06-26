#include <stdio.h>

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

int isValidCommand(int command);
int readCommand(void);

int isInsidePaddle(int y, int paddleY);
int moveLeftPaddle(int leftPaddleY, int command);
int moveRightPaddle(int rightPaddleY, int command);

int isTopOrBottomHit(int ballY);
int isLeftPaddleHit(int ballX, int ballY, int leftPaddleY);
int isRightPaddleHit(int ballX, int ballY, int rightPaddleY);

int updateBallDx(int ballDx, int ballX, int ballY, int leftPaddleY,
                 int rightPaddleY);
int updateBallDy(int ballDy, int ballY);

int getGoal(int ballX);
int updateLeftScore(int leftScore, int goal);
int updateRightScore(int rightScore, int goal);

int resetBallX(int ballX, int goal);
int resetBallY(int ballY, int goal);
int resetBallDx(int ballDx, int goal);
int resetBallDy(int ballDy, int goal);

void drawGame(int leftPaddleY, int rightPaddleY, int ballX, int ballY,
              int leftScore, int rightScore);
void printCell(int x, int y, int leftPaddleY, int rightPaddleY, int ballX,
               int ballY);
void printEmptyLines(void);
void printWinner(int leftScore, int rightScore);

int main(void) {
    int leftPaddleY = HEIGHT / 2;
    int rightPaddleY = HEIGHT / 2;
    int ballX = WIDTH / 2;
    int ballY = HEIGHT / 2;
    int ballDx = 1;
    int ballDy = 1;
    int leftScore = 0;
    int rightScore = 0;
    int command = 0;
    int goal = NO_GOAL;

    drawGame(leftPaddleY, rightPaddleY, ballX, ballY, leftScore, rightScore);

    while (leftScore < WIN_SCORE && rightScore < WIN_SCORE) {
        command = readCommand();
        leftPaddleY = moveLeftPaddle(leftPaddleY, command);
        rightPaddleY = moveRightPaddle(rightPaddleY, command);
        ballDx = updateBallDx(ballDx, ballX, ballY, leftPaddleY, rightPaddleY);
        ballDy = updateBallDy(ballDy, ballY);
        ballX += ballDx;
        ballY += ballDy;
        goal = getGoal(ballX);
        leftScore = updateLeftScore(leftScore, goal);
        rightScore = updateRightScore(rightScore, goal);
        ballDx = resetBallDx(ballDx, goal);
        ballDy = resetBallDy(ballDy, goal);
        ballX = resetBallX(ballX, goal);
        ballY = resetBallY(ballY, goal);
        drawGame(leftPaddleY, rightPaddleY, ballX, ballY, leftScore,
                 rightScore);
    }

    printWinner(leftScore, rightScore);

    return 0;
}

int isValidCommand(int command) {
    int result = command == 'a' || command == 'A' || command == 'z' ||
                 command == 'Z' || command == 'k' || command == 'K' ||
                 command == 'm' || command == 'M' || command == ' ';

    return result;
}

int readCommand(void) {
    int command = 0;

    while (!isValidCommand(command)) {
        command = getchar();

        if (command == '\n') {
            command = 0;
        }
    }

    return command;
}

int isInsidePaddle(int y, int paddleY) {
    int result = y >= paddleY - 1 && y <= paddleY + 1;

    return result;
}

int moveLeftPaddle(int leftPaddleY, int command) {
    int result = leftPaddleY;

    if ((command == 'a' || command == 'A') && leftPaddleY > MIN_PADDLE_Y) {
        result = leftPaddleY - 1;
    } else if ((command == 'z' || command == 'Z') &&
               leftPaddleY < MAX_PADDLE_Y) {
        result = leftPaddleY + 1;
    }

    return result;
}

int moveRightPaddle(int rightPaddleY, int command) {
    int result = rightPaddleY;

    if ((command == 'k' || command == 'K') && rightPaddleY > MIN_PADDLE_Y) {
        result = rightPaddleY - 1;
    } else if ((command == 'm' || command == 'M') &&
               rightPaddleY < MAX_PADDLE_Y) {
        result = rightPaddleY + 1;
    }

    return result;
}

int isTopOrBottomHit(int ballY) {
    int result = ballY <= 1 || ballY >= HEIGHT - 2;

    return result;
}

int isLeftPaddleHit(int ballX, int ballY, int leftPaddleY) {
    int result = ballX == LEFT_PADDLE_X + 1 &&
                 isInsidePaddle(ballY, leftPaddleY);

    return result;
}

int isRightPaddleHit(int ballX, int ballY, int rightPaddleY) {
    int result = ballX == RIGHT_PADDLE_X - 1 &&
                 isInsidePaddle(ballY, rightPaddleY);

    return result;
}

int updateBallDx(int ballDx, int ballX, int ballY, int leftPaddleY,
                 int rightPaddleY) {
    int result = ballDx;

    if (isLeftPaddleHit(ballX, ballY, leftPaddleY)) {
        result = 1;
    } else if (isRightPaddleHit(ballX, ballY, rightPaddleY)) {
        result = -1;
    }

    return result;
}

int updateBallDy(int ballDy, int ballY) {
    int result = ballDy;

    if (isTopOrBottomHit(ballY)) {
        result = -ballDy;
    }

    return result;
}

int getGoal(int ballX) {
    int goal = NO_GOAL;

    if (ballX <= 0) {
        goal = RIGHT_PLAYER_GOAL;
    } else if (ballX >= WIDTH - 1) {
        goal = LEFT_PLAYER_GOAL;
    }

    return goal;
}

int updateLeftScore(int leftScore, int goal) {
    int result = leftScore;

    if (goal == LEFT_PLAYER_GOAL) {
        result = leftScore + 1;
    }

    return result;
}

int updateRightScore(int rightScore, int goal) {
    int result = rightScore;

    if (goal == RIGHT_PLAYER_GOAL) {
        result = rightScore + 1;
    }

    return result;
}

int resetBallX(int ballX, int goal) {
    int result = ballX;

    if (goal != NO_GOAL) {
        result = WIDTH / 2;
    }

    return result;
}

int resetBallY(int ballY, int goal) {
    int result = ballY;

    if (goal != NO_GOAL) {
        result = HEIGHT / 2;
    }

    return result;
}

int resetBallDx(int ballDx, int goal) {
    int result = ballDx;

    if (goal == LEFT_PLAYER_GOAL) {
        result = -1;
    } else if (goal == RIGHT_PLAYER_GOAL) {
        result = 1;
    }

    return result;
}

int resetBallDy(int ballDy, int goal) {
    int result = ballDy;

    if (goal == LEFT_PLAYER_GOAL) {
        result = -1;
    } else if (goal == RIGHT_PLAYER_GOAL) {
        result = 1;
    }

    return result;
}

void drawGame(int leftPaddleY, int rightPaddleY, int ballX, int ballY,
              int leftScore, int rightScore) {
    int x;
    int y;

    printEmptyLines();
    printf("Player 1: %d | Player 2: %d\n", leftScore, rightScore);

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            printCell(x, y, leftPaddleY, rightPaddleY, ballX, ballY);
        }

        printf("\n");
    }

    printf("Controls: A/Z - left, K/M - right, Space - skip\n");
}

void printCell(int x, int y, int leftPaddleY, int rightPaddleY, int ballX,
               int ballY) {
    if (y == 0 || y == HEIGHT - 1) {
        printf("-");
    } else if (x == 0 || x == WIDTH - 1) {
        printf("|");
    } else if (x == ballX && y == ballY) {
        printf("o");
    } else if (x == LEFT_PADDLE_X && isInsidePaddle(y, leftPaddleY)) {
        printf("|");
    } else if (x == RIGHT_PADDLE_X && isInsidePaddle(y, rightPaddleY)) {
        printf("|");
    } else {
        printf(" ");
    }
}

void printEmptyLines(void) {
    int i;

    for (i = 0; i < HEIGHT; i++) {
        printf("\n");
    }
}

void printWinner(int leftScore, int rightScore) {
    if (leftScore >= WIN_SCORE) {
        printf("Congratulations! Player 1 wins!\n");
    } else if (rightScore >= WIN_SCORE) {
        printf("Congratulations! Player 2 wins!\n");
    }
}

