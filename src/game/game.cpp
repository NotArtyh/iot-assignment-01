#include "game/game.h"
#include "button/button.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SEQ_LENGHT 4

#define SCORE_FACTOR 100

uint8_t game_sequence[] = {1, 2, 3, 4};
int user_sequence_index = 0;
unsigned int game_score = 0;

const char *game_get_sequence_string() {
    static char buffer[MAX_SEQ_LENGHT + 1];
    for (int i = 0; i < MAX_SEQ_LENGHT; i++) {
        buffer[i] = '0' + game_sequence[i];
    }
    buffer[MAX_SEQ_LENGHT] = '\0';
    return buffer;
}

void game_shuffle_sequence() {
    srand(analogRead(0));
    for (int i = 0; i < MAX_SEQ_LENGHT; i++) {
        int tmp = game_sequence[i];
        int rand_index = rand() % MAX_SEQ_LENGHT;
        game_sequence[i] = game_sequence[rand_index];
        game_sequence[rand_index] = tmp;
    }
}

void game_reset() {
    user_sequence_index = 0;
    game_score = 0;
}

bool game_is_current_valid() {
    int button_sequence_index = game_sequence[user_sequence_index] - 1;
    if (button_is_pressed(button_sequence_index)) {
        user_sequence_index++;
        return true;
    }
    return false;
}

bool game_is_match_started() {
    if (button_get_current_pressed() == user_sequence_index &&
        user_sequence_index < MAX_SEQ_LENGHT) {
        return false;
    }
    return true;
}

bool game_all_match() {
    if (user_sequence_index != MAX_SEQ_LENGHT) {
        return false;
    }
    user_sequence_index = 0;
    return true;
}

int game_get_score() { return game_score; }

void game_update_score() { game_score += SCORE_FACTOR; }