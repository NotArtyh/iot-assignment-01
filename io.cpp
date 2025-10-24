#include "config.h"
#include "io.h"
#include <Arduino.h>
#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h> //DA CAMBIARE CON LA LIBRERIA PER OLED

// FADING LED VARIABLES
int fadeAmount;
int currIntensity;
currIntensity = 0;
fadeAmount = 5;

// input output logic, handles display for now

int greenLeds[] = {L1, L2, L3, L4};
int inputButtons[] = {B1, B2, B3, B4};

// initialize display

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

// SETUP DEI LED, BUTTONS E DISPLAY (spostare tutto il setup altrove intanto lo lascio qui)

void setupGreenLeds()
{
    for (int i = 0; i < NUM_GREEN_LEDS; i++)
    {
        pinMode(greenLeds[i], OUTPUT);
    }
}

void setupLs()
{
    pinMode(LS, OUTPUT);
}

void setupButtons()
{
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        pinMode(inputButtons[i], INPUT);
    }
}

void setupDisplay()
{
    lcd.init();
    lcd.backlight();
}

void setupIO()
{
    setupGreenLeds();
    setupLs();
    setupButtons();
    setupDisplay();
}

// FUNZIONI SUI LED

void pulseLs()
{
    analogWrite(LS, currIntensity);
    currIntensity = currIntensity + fadeAmount;
    if (currIntensity == 0 || currIntensity == 255)
    {
        fadeAmount = -fadeAmount;
    }
    delay(20);
}

void greenLedsOff()
{
    for (int i = 0; i < NUM_GREEN_LEDS; i++)
        digitalWrite(greenLeds[i], LOW);
}

void displayMessage(char message[]) {}
// forse non si riesce a gestire tutti i messaggi con una sola funzione display, dato che per ogni messaggio va settato la riga e colonna con messaggi diversi bisogna settare il punto di inizio diversamente
// propongo una soluzione del tipo: displayMessage(INITIAL_MESSAGE), displayMessage(WIN_MESSAGE) , ecc..
//  per poi gestire come il game status ciascun messaggio con uno switch case
//  tutto questo ragionamento è fatto per LCD