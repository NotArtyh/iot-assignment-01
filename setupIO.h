#ifndef __SETUPIO__
#define __SETUPIO__

// Indirizzo I2C del display
#define i2c_Address 0x3C // usa 0x3D se lo schermo rimane nero

// Dimensioni del display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // Pin di reset (non usato normalmente)

void setupGreenLeds();
void setupLs();
void setupButtons();
void setupDisplay();

void setupIO();

#endif