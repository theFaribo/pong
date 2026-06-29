#ifndef RENDER_H
#define RENDER_H

#include "game.h"

void draw_game(const GameState *state);
void print_cell(int x, int y, const GameState *state);
void print_empty_lines(void);
void print_winner(const GameState *state);

#endif
