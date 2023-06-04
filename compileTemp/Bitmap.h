/*----------------------------------------------------------------------

Dans cette librairie sont stockés toutes les images bitmap à afficher
sur les matrices. Chaque ligne correspond à une ligne de la matrice.
Un 0 signifie que le pixel est éteint et un 1 qu'il est allumé.

-----------------------------------------------------------------------*/

static const uint8_t PROGMEM
  clear_bmp[] =
  { B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 };

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 };
