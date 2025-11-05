#include "config.h"
#include <Arduino.h>

int difficulty = 1; // mu serve globalmente

void potentiometer_init()
{
    pinMode(POT, INPUT);
}

// Aggiorna la difficoltà leggendo il potenziometro
void update_difficulty()
{
    int potValue = analogRead(POT);
    difficulty = map(potValue, 0, 1023, 1, 4);
}

// Restituisce il valore attuale della difficoltà
int read_difficulty()
{
    return difficulty;
}
