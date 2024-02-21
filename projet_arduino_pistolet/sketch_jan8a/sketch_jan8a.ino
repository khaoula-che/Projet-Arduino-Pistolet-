#include <PCM.h>

// Déclaration des broches
int led1 = 3; // Broche PWM
int led2 = 5; // Broche PWM
int led3 = 6; // Broche PWM
int led4 = 9; // Broche PWM
int led5 = 10; // Broche PWM
int led6 = 11; // Broche PWM
int buzzer = A4;
int pot = A5;
int RED = A1;
int GRN = A2;
int BLU = A3;
#define bouton1 13
#define bouton2 2 

// Tableaux pour les échantillons sonores
const unsigned char sample[] PROGMEM = {
  37, 12, 15, 20, 65, 35, 19, 18, 20, 12, 130, 23, 26, 55, 37, 
  35, 72, 144, 42, 24, 40, 18, 10, 17, 44, 11, 37, 130, 16, 26, 
  19, 17, 9, 16, 15, 21, 15, 12, 17, 15, 15, 18, 11, 12, 7, 11, 
  4, 10, 13, 27, 110, 27, 57, 23, 15, 16, 17, 18, 25, 130, 45, 35, 
  50, 27, 24, 21, 15, 16, 21, 13, 16, 17, 9, 21, 8, 12, 16, 14, 
  12, 8, 10, 8, 9, 12, 14, 16, 9, 10, 16, 23, 16, 9, 14, 16, 
  17, 16, 16, 20, 23, 21
};

const unsigned char sample2[] PROGMEM = {
  0, 10, 20, 30, 40, 50, 60, 70,
  80, 90, 100, 110, 120, 130, 140, 150,
  160, 170, 180, 190, 200, 210, 220, 230,
  240, 250, 255, 250, 240, 230, 220, 210,
  200, 190, 180, 170, 160, 150, 140, 130,
  120, 110, 100, 90, 80, 70, 60, 50,
  40, 30, 20, 10, 0
};
void setup() {
  // Configuration des broches en entrée ou sortie
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(pot, INPUT);

  // Démarrage de la lecture des échantillons sonores
  startPlayback(sample, sizeof(sample));
  startPlayback(sample2, sizeof(sample2));
}

void loop() {
  // Lecture des états des boutons
  int etatBouton1 = digitalRead(bouton1);
  int etatBouton2 = digitalRead(bouton2);

  // Lecture de la valeur du potentiomètre (réglage volume)
  int POT = analogRead(A5);
  int volume = map(POT, 0, 1023, 0, 255);
  analogWrite(buzzer, POT);

  if (etatBouton1 == HIGH && etatBouton2 == HIGH) {
    // Éteindre les LEDs
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
    analogWrite(led4, 0);
    analogWrite(led5, 0);
    analogWrite(led6, 0);

    // Faire clignoter la LED RGB
    for (int i = 0; i <= 255; i++) {
      analogWrite(RED, i);
      delay(2);
    }
    for (int i = 255; i >= 0; i--) {
      analogWrite(RED, i);
      delay(2);
    }
    for (int i = 0; i <= 255; i++) {
      analogWrite(GRN, i);
      delay(2);
    }
    for (int i = 255; i >= 0; i--) {
      analogWrite(GRN, i);
      delay(2);
    }
    for (int i = 0; i <= 255; i++) {
      analogWrite(BLU, i);
      delay(2);
    }
    for (int i = 255; i >= 0; i--) {
      analogWrite(BLU, i);
      delay(2);
    }
    noTone(buzzer);
  } else if (etatBouton1 == LOW) {
    // Allumer les LEDs avec des intensités différentes
    analogWrite(led1, 255); // LED1 avec l'intensité maximale
    delay(500);
    analogWrite(led2, 90); // LED2 avec l'intensité moyenne
    delay(500);
    analogWrite(led3, 25);  // LED3 avec l'intensité faible
    delay(500);

    // répéter l'effet
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
    delay(500); // Délai avant de recommencer l'effet
    // Son du bouton1b
    for (int i = 0; i < sizeof(sample) / sizeof(sample[0]); i++) {
      int noteDuration = 100;
      tone(buzzer, pgm_read_byte_near(sample + i), noteDuration);
      delay(30);,
    }
    noTone(buzzer);
  } else if (etatBouton2 == LOW) {
    // Allumer les LEDs avec des intensités différentes
    analogWrite(led4, 255); // LED3 avec l'intensité maximale
    delay(500);
    analogWrite(led5, 90); // LED4 avec l'intensité moyenne
    delay(500);
    analogWrite(led6, 25);  // LED5 avec l'intensité faible
    delay(500);

    // répéter l'effet
    analogWrite(led4, 0);
    analogWrite(led5, 0);
    analogWrite(led6, 0);
    delay(500); // Délai avant de recommencer l'effet
    // Son, on parcourt le tableau sample2
    for (int i = 0; i < sizeof(sample2) / sizeof(sample2[0]); i++) {
      int noteDuration = 100;
      tone(buzzer, pgm_read_byte_near(sample2 + i), noteDuration);
      delay(30);
    }
    noTone(buzzer);
  } 
}
