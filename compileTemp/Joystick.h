#include "Adafruit_LEDBackpack.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "Bitmap.h"


#define PIN_blue_button 2
#define PIN_green_button 4

#define PIN_joy_droit A0
#define PIN_joy_gauche A2
#define PIN_joy_haut A3
#define PIN_joy_bas A1

Adafruit_8x8matrix matrix0 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix1 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix3 = Adafruit_8x8matrix();

void init_matrix()
{
  matrix0.begin(0x70);  // L'adresse en paramètre
  matrix1.begin(0x71);
  matrix2.begin(0x72);
  matrix3.begin(0x73);
}

void init_buttons()
{
  pinMode(PIN_blue_button, INPUT_PULLUP); // init de mon bouton
  pinMode(PIN_green_button, INPUT_PULLUP);
}

void init_joystick()
{
  pinMode(PIN_joy_droit,INPUT);
  pinMode(PIN_joy_gauche,INPUT);
  pinMode(PIN_joy_haut,INPUT);
  pinMode(PIN_joy_bas,INPUT);
}

void clear_matrix(Adafruit_8x8matrix matrix)
{
  matrix.drawBitmap(0, 0, clear_bmp, 8, 8, LED_OFF);
  matrix.writeDisplay();
}




