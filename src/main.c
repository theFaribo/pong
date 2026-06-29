#include "game.h"
#include "input.h"
#include "render.h"

int main(void) {
    GameState state;
    Action action;

    init_game(&state);
    draw_game(&state);

    while (!is_game_finished(&state)) {
        action = read_action();
        update_game(&state, action);
        draw_game(&state);
    }

    print_winner(&state);

    return 0;
}
