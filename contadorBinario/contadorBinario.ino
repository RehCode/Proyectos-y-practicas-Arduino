#define IZQ 0
#define DER 1

byte luces = B00000001;
byte direccion = 0;

void setup() {
  
  DDRD = B11111111;

}

void loop() {

  if (luces == B10000000 ) {
    direccion = DER;
  } else if (luces == B00000001) {
    direccion = IZQ;
  }
  
  PORTD = luces;

  if (direccion == DER) {
    luces = luces >> 1;
  } else {
    luces = luces << 1;
  }
  
  delay(30);
  
}
