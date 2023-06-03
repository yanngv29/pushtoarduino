#include <Adafruit_NeoPixel.h>

#define PIN_1 2
#define PIN_2 4
#define PIN_3 6
#define PIN_4 8
#define PIN_5 10

#define STRIPSIZE 20

//   Parameter 1 = number of pixels in strip
//   Parameter 2 = pin number (most are valid)
//   Parameter 3 = pixel type flags, add together as needed

//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)

//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(STRIPSIZE, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(STRIPSIZE, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(STRIPSIZE, PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_4 = Adafruit_NeoPixel(STRIPSIZE, PIN_4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_5 = Adafruit_NeoPixel(STRIPSIZE, PIN_5, NEO_GRB + NEO_KHZ800);

void activate_led(uint16_t x, uint16_t y, char c) {

  switch(y) {

    case 1:
      if(c == 'R' || c == 'r') { strip_1.setPixelColor(x, 255, 0, 0); }
      if(c == 'G' || c == 'g') { strip_1.setPixelColor(x, 0, 255, 0); }
      if(c == 'B' || c == 'b') { strip_1.setPixelColor(x, 0, 0, 255); }
      break;

    case 2:
      if(c == 'R' || c == 'r') { strip_2.setPixelColor(x, 255, 0, 0); }
      if(c == 'G' || c == 'g') { strip_2.setPixelColor(x, 0, 255, 0); }
      if(c == 'B' || c == 'b') { strip_2.setPixelColor(x, 0, 0, 255); }
      break;

    case 3:
      if(c == 'R' || c == 'r') { strip_3.setPixelColor(x, 255, 0, 0); }
      if(c == 'G' || c == 'g') { strip_3.setPixelColor(x, 0, 255, 0); }
      if(c == 'B' || c == 'b') { strip_3.setPixelColor(x, 0, 0, 255); }
      break;

    case 4:
      if(c == 'R' || c == 'r') { strip_4.setPixelColor(x, 255, 0, 0); }
      if(c == 'G' || c == 'g') { strip_4.setPixelColor(x, 0, 255, 0); }
      if(c == 'B' || c == 'b') { strip_4.setPixelColor(x, 0, 0, 255); }
      break;

    case 5:
      if(c == 'R' || c == 'r') { strip_5.setPixelColor(x, 255, 0, 0); }
      if(c == 'G' || c == 'g') { strip_5.setPixelColor(x, 0, 255, 0); }
      if(c == 'B' || c == 'b') { strip_5.setPixelColor(x, 0, 0, 255); }
      break;
  }

  strip_1.show();
  strip_2.show();
  strip_3.show();
  strip_4.show();
  strip_5.show();  
}

void activate_column(uint16_t col, uint16_t start, uint16_t length, char color) {

  for(uint16_t i = 0; i < length; i ++) {
    activate_led(start+i, col, color);
  }
}

void activate_line(uint16_t line, uint16_t start, uint16_t length, char color) {

  for(uint16_t i = 0; i < length; i ++) {
    activate_led(line, start+i, color);
  }
}

void diagonal(uint16_t x, uint16_t y, bool ud, bool lr, uint16_t length, char color) {

  if(ud && lr == false) {
    for(uint16_t i = 0; i < length; i++) {
      activate_led(x-i, y-i, color);
    }
  }

  else if(ud && lr) {
    for(uint16_t i = 0; i < length; i++) {
      activate_led(x-i, y+i, color);
    }
  }

  else if(ud == false && lr) {
    for(uint16_t i = 0; i < length; i++) {
      activate_led(x+i, y+i, color);
    }
  }

  else if(ud == false && lr == false) {
    for(uint16_t i = 0; i < length; i++) {
      activate_led(x+i, y-i, color);
    }
  }
}


void rainbow() {

  uint16_t i, j;
  byte color_pos;

  for(j = 0; j < 256 * 5; j++) {
    for(i = 0; i < STRIPSIZE; i++) {

      color_pos = (i+j) & 255;

      if(color_pos < 85)
      {
        strip_1.setPixelColor(i, strip_1.Color(color_pos * 3, 255 - color_pos * 3, 0));
        strip_2.setPixelColor(i, strip_2.Color(color_pos * 3, 255 - color_pos * 3, 0));
        strip_3.setPixelColor(i, strip_3.Color(color_pos * 3, 255 - color_pos * 3, 0));
        strip_4.setPixelColor(i, strip_4.Color(color_pos * 3, 255 - color_pos * 3, 0));
        strip_5.setPixelColor(i, strip_5.Color(color_pos * 3, 255 - color_pos * 3, 0));       
      }
      else if(color_pos < 170)
      {
        color_pos -= 85;
        strip_1.setPixelColor(i, strip_1.Color(255 - color_pos * 3, 0, color_pos * 3));
        strip_2.setPixelColor(i, strip_2.Color(255 - color_pos * 3, 0, color_pos * 3));
        strip_3.setPixelColor(i, strip_3.Color(255 - color_pos * 3, 0, color_pos * 3));
        strip_4.setPixelColor(i, strip_4.Color(255 - color_pos * 3, 0, color_pos * 3));
        strip_5.setPixelColor(i, strip_5.Color(255 - color_pos * 3, 0, color_pos * 3));     
      } 
      else
      {
        color_pos -= 170;
        strip_1.setPixelColor(i, strip_1.Color(0, color_pos * 3, 255 - color_pos * 3));
        strip_2.setPixelColor(i, strip_2.Color(0, color_pos * 3, 255 - color_pos * 3));
        strip_3.setPixelColor(i, strip_3.Color(0, color_pos * 3, 255 - color_pos * 3));
        strip_4.setPixelColor(i, strip_4.Color(0, color_pos * 3, 255 - color_pos * 3));
        strip_5.setPixelColor(i, strip_5.Color(0, color_pos * 3, 255 - color_pos * 3));
      }
    }

    strip_1.show();
    strip_2.show();
    strip_3.show();
    strip_4.show();
    strip_5.show();

    delay(1);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout

void rainbow_cycle(uint16_t nb) {

  uint16_t i, j;
  byte color_pos;

  for(j = 0; j < 256 * nb; j++) { // 5 cycles of all colors on wheel
    for(i = 0; i < STRIPSIZE; i++) {

      color_pos = (i+j) & 255;

      if(color_pos < 85)
      {
        strip_1.setPixelColor(i, strip_1.Color(color_pos * 3, 255 - color_pos * 3, 0));
        strip_2.setPixelColor(i, strip_2.Color(color_pos * 3, 255 - color_pos * 3, 0));
        strip_3.setPixelColor(i, strip_3.Color(color_pos * 3, 255 - color_pos * 3, 0));
        strip_4.setPixelColor(i, strip_4.Color(color_pos * 3, 255 - color_pos * 3, 0));
        strip_5.setPixelColor(i, strip_5.Color(color_pos * 3, 255 - color_pos * 3, 0));       
      }
      else if(color_pos < 170)
      {
        color_pos -= 85;
        strip_1.setPixelColor(i, strip_1.Color(255 - color_pos * 3, 0, color_pos * 3));
        strip_2.setPixelColor(i, strip_2.Color(255 - color_pos * 3, 0, color_pos * 3));
        strip_3.setPixelColor(i, strip_3.Color(255 - color_pos * 3, 0, color_pos * 3));
        strip_4.setPixelColor(i, strip_4.Color(255 - color_pos * 3, 0, color_pos * 3));
        strip_5.setPixelColor(i, strip_5.Color(255 - color_pos * 3, 0, color_pos * 3));     
      } 
      else
      {
        color_pos -= 170;
        strip_1.setPixelColor(i, strip_1.Color(0, color_pos * 3, 255 - color_pos * 3));
        strip_2.setPixelColor(i, strip_2.Color(0, color_pos * 3, 255 - color_pos * 3));
        strip_3.setPixelColor(i, strip_3.Color(0, color_pos * 3, 255 - color_pos * 3));
        strip_4.setPixelColor(i, strip_4.Color(0, color_pos * 3, 255 - color_pos * 3));
        strip_5.setPixelColor(i, strip_5.Color(0, color_pos * 3, 255 - color_pos * 3));
      }
    }

    strip_1.show();
    strip_2.show();
    strip_3.show();
    strip_4.show();
    strip_5.show();

    delay(1);
  }
}