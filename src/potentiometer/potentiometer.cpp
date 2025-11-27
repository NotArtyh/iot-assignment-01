#include "config.h"
#include <Arduino.h>

int factor = 1; // mu serve globalmente

void pot_init() { pinMode(POT, INPUT); }

// Aggiorna la difficoltà leggendo il potenziometro
void pot_update_factor() {
    int potValue = analogRead(POT);
    factor = map(potValue, 0, 1023, 1, 4);
}

// Restituisce il valore attuale della difficoltà
int pot_get_factor() { return factor; }
