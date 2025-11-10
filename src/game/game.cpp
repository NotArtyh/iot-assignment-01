#include "game/game.h"
#include "button/button.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SEQ_LENGHT 4
uint8_t game_sequence[] = {1, 2, 3, 4};
int user_sequence_index = 0;

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

// give proper naming and implement
void game_reset() {
    user_sequence_index = 0;
    game_shuffle_sequence();
}

bool game_is_current_valid() {
    int button_sequence_index = game_sequence[user_sequence_index] - 1;
    if (button_is_pressed(button_sequence_index)) {
        user_sequence_index++;
        return true;
    }
    return false;
}

// bool game_matched_sequence() {
//     for (int i = 0; i < MAX_SEQ_LENGHT; i++) {
//         if (button_is_pressed(i) && button_get_last_pressed() == i) {
//             // on button that is last pressed independt of the iteration
//             if (game_sequence[user_sequence_index] == i) {
//                 // still matching the sequence
//                 user_sequence_index++;
//                 return true;
//             } else {
//                 // not matching the sequence either not all button pressed or
//                 // wrong sequence
//                 return false;
//             }
//         }
//     }

//     for (size_t i = 0; i < button_get_all_pressed(); i++) {
//         if (!game_is_current_digit_pressed()) {
//             return false; // fail condition the button is wrong
//         }
//     }
//     return false; // no button has been pressed yet
//     if (user_sequence_index == MAX_SEQ_LENGHT) {
//         return true; // win condition, the user sequence has same lenght and
//     }
// }

bool game_is_match_started() {
    // if (button_get_last_pressed() == -1) {
    //     return false; // no input yet;
    // }
    // return true;

    if (button_get_current_pressed() == user_sequence_index &&
        user_sequence_index < MAX_SEQ_LENGHT) {
        return false; // no input yet
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

int game_get_user_sequence_index() { return user_sequence_index; }
