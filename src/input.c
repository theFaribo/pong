#include <stdio.h>

#include "input.h"

Action parse_command(int command) {
    Action action = ACTION_NONE;

    if (command == 'a' || command == 'A') {
        action = ACTION_LEFT_UP;
    } else if (command == 'z' || command == 'Z') {
        action = ACTION_LEFT_DOWN;
    } else if (command == 'k' || command == 'K') {
        action = ACTION_RIGHT_UP;
    } else if (command == 'm' || command == 'M') {
        action = ACTION_RIGHT_DOWN;
    } else if (command == ' ') {
        action = ACTION_SKIP;
    }

    return action;
}

Action read_action(void) {
    int command;
    Action action = ACTION_NONE;

    while (action == ACTION_NONE) {
        command = getchar();

        if (command != '\n') {
            action = parse_command(command);
        }
    }

    return action;
}
