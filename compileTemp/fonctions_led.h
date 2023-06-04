#include <Adafruit_NeoPixel.h>

#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5
#define PIN_5 6
#define PIN_6 7
#define PIN_7 8
#define PIN_8 9

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
Adafruit_NeoPixel strip_6 = Adafruit_NeoPixel(STRIPSIZE, PIN_6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_7 = Adafruit_NeoPixel(STRIPSIZE, PIN_7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_8 = Adafruit_NeoPixel(STRIPSIZE, PIN_8, NEO_GRB + NEO_KHZ800);

void clear() {

  strip_1.clear();
  strip_2.clear();
  strip_3.clear();
  strip_4.clear();
  strip_5.clear();
  strip_6.clear();
  strip_7.clear();
  strip_8.clear();
}

/**
*
* @return active un LED sur la matrice 
*
* @param line : correspond à la ligne recherchée
* @param col : correspond à la colonne recherchée 
* @param color : correspond à la couleur demandée
*
*/

void activate_led(uint16_t line, uint16_t col, char color) {

  char letter = toupper(color); // On passe le char en majuscule 

  // On regarde la colonne demandée ( une colonne est un bandeau de LED )
  switch(col) {

    case 0: // Si le 0 est demandé - on active le premier bandeau

      // On fait un cas pour chaque couleur et on active le LED à la ligne " line " sur le bandeau
      if(letter == 'R') { strip_1.setPixelColor(line, 255, 0, 0); } // Les 3 dernières valeurs correspondent aux valeurs RGB du LED
      if(letter == 'G') { strip_1.setPixelColor(line, 0, 255, 0); }
      if(letter == 'B') { strip_1.setPixelColor(line, 0, 0, 255); }
      break;

    case 1:
      if(letter == 'R') { strip_2.setPixelColor(line, 255, 0, 0); }
      if(letter == 'G') { strip_2.setPixelColor(line, 0, 255, 0); }
      if(letter == 'B') { strip_2.setPixelColor(line, 0, 0, 255); }
      break;

    case 2:
      if(letter == 'R') { strip_3.setPixelColor(line, 255, 0, 0); }
      if(letter == 'G') { strip_3.setPixelColor(line, 0, 255, 0); }
      if(letter == 'B') { strip_3.setPixelColor(line, 0, 0, 255); }
      break;

    case 3:
      if(letter == 'R') { strip_4.setPixelColor(line, 255, 0, 0); }
      if(letter == 'G') { strip_4.setPixelColor(line, 0, 255, 0); }
      if(letter == 'B') { strip_4.setPixelColor(line, 0, 0, 255); }
      break;

    case 4:
      if(letter == 'R') { strip_5.setPixelColor(line, 255, 0, 0); }
      if(letter == 'G') { strip_5.setPixelColor(line, 0, 255, 0); }
      if(letter == 'B') { strip_5.setPixelColor(line, 0, 0, 255); }
      break;

    case 5:
      if(letter == 'R') { strip_6.setPixelColor(line, 255, 0, 0); }
      if(letter == 'G') { strip_6.setPixelColor(line, 0, 255, 0); }
      if(letter == 'B') { strip_6.setPixelColor(line, 0, 0, 255); }
      break;

    case 6:
      if(letter == 'R') { strip_7.setPixelColor(line, 255, 0, 0); }
      if(letter == 'G') { strip_7.setPixelColor(line, 0, 255, 0); }
      if(letter == 'B') { strip_7.setPixelColor(line, 0, 0, 255); }
      break;

    case 7:
      if(letter == 'R') { strip_8.setPixelColor(line, 255, 0, 0); }
      if(letter == 'G') { strip_8.setPixelColor(line, 0, 255, 0); }
      if(letter == 'B') { strip_8.setPixelColor(line, 0, 0, 255); }
      break;

    // C'est ici qu'il faut modifier le code pour ajouter d'autres bandeaux de LED    
  }

  // On affiche les LEDs à la fin de la boucle ( nous n'aurons plus à le faire dans les autres fonctions )
  strip_1.show();
  strip_2.show();
  strip_3.show();
  strip_4.show();
  strip_5.show(); 
  strip_6.show();  
  strip_7.show(); 
  strip_8.show(); 
}

/** 
*
* Maintenant que la fonction " activate_led " nous permet de nous deplacer
* de manière matricielle : nous avons la possibilité de l'utiliser pour concevoir
* des fonctions nous permettant d'afficher des formes sur la grille de LEDs
*
*/ 

/**
*
* @return : active une colonne sur la matrice 
* 
* @param col : correspond à la colonne que vous voulez allumer
* @param start : correspond à la au LED d'où partira l'affichage ( du haut vers le bas )
* @param length : correspond à la taille de la colonne à afficher
* @param color :  correspond à la couleur demandée
*
*/

void activate_column(uint16_t col, uint16_t start, uint16_t length, char color) {

  // Grâce à la fonction activate_led() nous pouvons simplement boucler notre déplacement sur la grille de LEDs
  for(uint16_t i = 0; i < length; i ++) {
    activate_led(start+i, col, color);
  }
}

/**
*
* @return : active une ligne sur la matrice 
* 
* @param line : correspond à la ligne que vous voulez allumer
* @param start : correspond à la au LED d'où partira l'affichage ( de la gauche vers la droite )
* @param length : correspond à la taille de la ligne à afficher
* @param color : correspond à la couleur demandée
*
*/

void activate_line(uint16_t line, uint16_t start, uint16_t length, char color) {

  for(uint16_t i = 0; i < length; i ++) {
    activate_led(line, start+i, color);
  }
}

/**
*
* @return : active une diagonale sur la matrice 
* 
* @param line : correspond à la ligne 
* @param col : correspond à la colonne
* @param ud : Signifie UP/DOWN, un booléen qui True -> UP et False -> DOWN
* @param lr : Signifie LEFT/RIGHT, un booléen qui True -> LEFT et False -> RIGH*
* @param color : correspond à la couleur demandée
*
*/

void activate_diagonal(uint16_t line, uint16_t col, bool ud, bool lr, uint16_t length, char color) {

  // 4 directions possibles : 4 if -

  if(ud && lr == false) {
    for(uint16_t i = 0; i < length; i++) {
      activate_led(line-i, col-i, color); // On boucle dans la diago correspondant
    }
  }

  else if(ud && lr) {
    for(uint16_t i = 0; i < length; i++) {
      activate_led(line-i, col+i, color);
    }
  }

  else if(ud == false && lr) {
    for(uint16_t i = 0; i < length; i++) {
      activate_led(line+i, col+i, color);
    }
  }

  else if(ud == false && lr == false) {
    for(uint16_t i = 0; i < length; i++) {
      activate_led(line+i, col-i, color);
    }
  }
}

/**
*
* @return : active une diagonale sur la matrice 
* 
* @param c : correspond à la lettre à afficher
* @param color : correspond à la couleur de cette lettre
*
*/

void alphabet(char c, char color) {

  char letter = toupper(c);

  switch(letter) {

    case 'A' :
      activate_column(0, 3, 17, color);
      activate_diagonal(2, 0, true, true, 3, color);
      activate_diagonal(3, 0, true, true, 3, color);
      activate_line(9, 0, 5, color);
      activate_line(10, 0, 5, color);
      activate_diagonal(1, 3, false, true, 2, color);
      activate_diagonal(2, 3, false, true, 2, color);
      activate_column(4, 3, 17, color);
      break;


    case 'B' :
      activate_line(11, 2, 2, color);
      activate_line(19, 2, 3, color);
      activate_column(4, 3, 5, color);
      activate_column(4, 12, 7, color);
      activate_column(0, 0, 20, color);
      activate_column(1, 0, 20, color);
      activate_diagonal(0, 2, false, true, 3, color);
      activate_diagonal(10, 2, true, true, 3, color);   
      break;

    case 'C' :
      activate_line(0, 2, 3, color);
      activate_led(1, 1, color);
      activate_column(4, 0, 3, color);
      activate_line(2, 2, 3, color);
      activate_column(1, 3, 14, color);
      activate_line(17, 2, 3, color);
      activate_column(17, 0, 3, color);
      activate_line(19, 2, 3, color);
      activate_led(18, 1, color);
      activate_column(0, 2, 16, color);
      activate_led(18, 4, color);
      break;

    case 'D' : 
      activate_column(0, 0, 20, color);
      activate_column(1, 0, 20, color);
      activate_diagonal(0, 2, false, true, 2, color);
      activate_column(4, 3, 14, color);
      activate_diagonal(19, 2, true, true, 2, color);
      break;

    case 'E' :
      activate_column(0, 0, 20, color);
      activate_line(0, 1, 4, color);
      activate_line(1, 1, 4, color);
      activate_line(9, 1, 2, color);
      activate_line(18, 1, 4, color);
      activate_line(19, 1, 4, color);
      break;

    case 'F' :
      activate_column(0, 0, 20, color);
      activate_column(1, 0, 20, color);
      activate_line(0, 2, 3, color);
      activate_line(1, 2, 3, color);
      activate_line(9, 2, 2, color);
      activate_line(10, 2, 2, color);
      break;

    case 'G' :
      activate_line(0, 2, 3, color);
      activate_led(1, 1, color);
      activate_column(4, 0, 3, color);
      activate_line(2, 2, 3, color);
      activate_column(1, 3, 14, color);
      activate_line(17, 2, 3, color);
      activate_column(17, 0, 3, color);
      activate_line(19, 2, 3, color);
      activate_led(18, 1, color);
      activate_column(0, 2, 16, color);
      activate_led(18, 4, color);
      activate_column(4, 10, 7, color);
      activate_column(3, 10, 2, color);
      break;

    case 'H' :
      activate_column(0, 0, 20, color);
      activate_column(1, 0, 20, color);
      activate_line(9 , 2, 1, color);
      activate_line(10, 2, 1, color);
      activate_line(11, 2, 1, color);
      activate_column(3, 0, 20, color);
      activate_column(4, 0, 20, color);
      break;

    case 'I' :
      activate_line(0, 0, 5, color);
      activate_line(1, 0, 5, color);
      activate_line(18, 0, 5, color);
      activate_column(2, 1, 18, color);
      activate_line(19, 0, 5, color);
      break;

    case 'J' :
      activate_line(0, 0, 5, color);
      activate_line(1, 0, 5, color);
      activate_column(2, 1, 17, color);
      activate_led(18, 1, color);
      activate_led(17, 0, color);
      break;

    case 'K' :
      activate_column(0, 0, 20, color);
      activate_column(1, 0, 20, color);
      activate_diagonal(9, 0, true, true, 5, color);
      activate_diagonal(11, 0, false, true, 5, color);
      break;

    case 'L' :
      activate_column(0, 0, 20, color);
      activate_column(1, 0, 20, color);
      activate_line(18, 2, 3, color);
      activate_line(19, 2, 3, color);
      break;

    case 'M' :
      activate_column(0, 0, 20, color);
      activate_column(4, 0, 20, color);
      activate_diagonal(1, 1, false, true, 2, color);
      activate_diagonal(2, 1, false, true, 2, color);
      activate_led(1, 3, color);
      activate_led(2, 3, color);
      break;

    case 'N' :
      activate_column(0, 0, 20, color);
      activate_column(4, 0, 20, color);
      activate_led(2, 1, color);
      activate_led(6, 2, color);
      activate_led(9, 3, color);
      activate_led(4, 1, color);
      activate_led(7, 2, color);
      activate_led(11, 3, color);
      break;

    case 'O' :
      activate_column(0, 0, 20, color);
      activate_column(4, 0, 20, color);
      activate_line(0, 0, 5, color);
      activate_line(1,0, 5, color);
      activate_line(19, 0, 5, color);
      activate_line(18, 0, 5, color);
      break; 

    case 'P' :
      activate_column(0, 0, 20, color);
      activate_column(1, 0, 20, color);
      activate_line(0, 0, 5, color);
      activate_line(1,0, 5, color);
      activate_column(4, 0, 7, color);
      activate_line(6, 0, 5, color);
      activate_line(7, 0, 5, color);
      break; 

    case 'S' :
      activate_line(0, 0, 5, color);
      activate_column(0, 0, 9, color);
      activate_line(10, 0, 5, color);
      activate_column(4, 10, 10, color);
      activate_line(19, 0, 5, color);
      break; 

    default : 
      activate_line(0, 0, 5, color);
      break;
  }
}

/**
*
* @return : affiche un arc en ciel
* 
*/

// Marche sur 5 strip uniquement 

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