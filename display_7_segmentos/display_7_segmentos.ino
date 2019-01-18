
byte conteo = 0;
byte unidades = 0;
byte decenas = 0;
const byte numeros[10] = {
   //ABCDEFG /dp
   B11111100, // 0
   B01100000, // 1
   B11011010, // 2
   B11110010, // 3
   B01100110, // 4
   B10110110, // 5
   B00111110, // 6
   B11100000, // 7
   B11111110, // 8
   B11100110, // 9
};

unsigned long previousMillis = 0;
const long intervalo = 150;
unsigned long currentMillis;

void setup() {
  DDRD = B11111111;
  DDRB |= B00110000;
}

void loop() {
  unidades = conteo % 10;
  decenas = conteo / 10;

  // unidades
  PORTB = B00010000;
  PORTD = numeros[unidades];
  delay(1);

  // decenas
  PORTB = B00100000;
  PORTD = numeros[decenas];
  delay(1);

  currentMillis = millis();

  if (currentMillis - previousMillis >= intervalo) {
    previousMillis = currentMillis;
    conteo += 1;

    if (conteo > 99) {
      conteo = 0;
    }
  }

}

void prueba_segmentos() {
  PORTD = conteo;

  if (conteo == 0) {
    conteo = 1;
  }
  conteo = conteo << 1;
  delay(500);
}

