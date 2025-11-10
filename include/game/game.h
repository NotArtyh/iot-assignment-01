#ifndef GAME_H
#define GAME_H

const char *game_get_sequence_string();
void game_shuffle_sequence();

// bool game_is_validate_sequence();
// bool game_matched_sequence();

bool game_is_match_started();
bool game_is_current_valid();
bool game_all_match();

int game_get_user_sequence_index();

#endif