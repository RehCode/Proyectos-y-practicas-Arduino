#define IZQ 0
#define DER 1

byte luces = B00000001;
byte direccion = IZQ;
byte velocidad = 90;
boolean soltoA = true;
boolean soltoB = true;

void setup() {

  DDRD = B11111111; // salida leds
  DDRB = B00000000; // entrada botones
  PORTB = B00111111; // pull-ups

}

void loop() {

  //  botones
  if ( ((PINB & B00100000) == 0) && (luces == B00100000) ){
    soltoA = false;
  }

  if ( ((PINB & B00100000) == 0) && (luces == B10000000)){
    if (soltoA) {
      direccion = DER;
      velocidad -= 5;
      if (velocidad <= 30) {
        velocidad = 35;
      }
    }
  }

  if ( ((PINB & B00010000) == 0) && (luces == B00000100) ){
    soltoB = false;
  }

  if ( ((PINB & B00010000) == 0) && (luces == B00000001)){
    if (soltoB) {
      direccion = IZQ;
    }
  }

  // reset
  if ( ((PINB & B00110000) == 0) && (luces == B00000000) ){
    direccion = IZQ;
    luces = B00000001;
    velocidad = 90;
    soltoA = true;
    soltoB = true;

    PORTD = 0xFF;
    delay(800);
    PORTD = 0x00;
    delay(500);
    PORTD = B01000000;
    delay(500);
    PORTD = B10000000;
    delay(300);
    PORTD = B00100000;
    delay(500);
    PORTD = 0x00;
    delay(800);
  }

  // mostrar
  PORTD = luces;

  // recorrer
  if (direccion == DER) {
    luces = luces >> 1;
  } else {
    luces = luces << 1;
  }

  delay(velocidad);

}
