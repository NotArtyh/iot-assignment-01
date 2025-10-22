#define L1 13
#define L2 12
#define L3 11
#define L4 10
#define LS 3
#define B1 9
#define B2 8
#define B3 7
#define B4 6
#define POT A0

typedef enum {
  ST_INITIAL,
  ST_SLEEP,
  ST_SETUP,
  ST_ROUND,
  ST_LSOE,
  ST_WIN,
} State;

State currentState = ST_INITIAL;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (currentState) {
    case ST_INITIAL:
      handle_initial_state();

      // transiton
      break;
    case ST_SLEEP:

      break;
    default:
      break;
  }
}

void handle_initial_state() {
  // In the initial state, all green leds should be off but led LS that pulses (fading in and out),
  // waiting for some player to start the game. The LCD should display the message “Welcome to TOS! Press B1 to Start” (on multiple lines).

  display_message_lcd("Welcome to TOS! Press B1 to Start");
}

void display_message_lcd(char message[]) {

}