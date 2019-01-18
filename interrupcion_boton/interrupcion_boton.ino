#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

volatile int contador = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  int en = 0;
  Serial.begin(9600);
  attachInterrupt(0, interrupcion, FALLING); // CHANGE - FALLING
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Interrupciones:");
  
}

void interrupcion() {
  contador++;
}

void loop() {
  Serial.println(contador);
  lcd.setCursor(0, 1);
  lcd.print(contador);  
  delay(500);
}
