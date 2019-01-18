#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// pad numerico
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = 
  {{'1', '2', '3', 'A'},
   {'4', '5', '6', 'B'},
   {'7', '8', '9', 'C'},
   {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};
Keypad kpad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char key;

// leds indicadores
byte led_hab = 11, led_des = 12;

// password
char password[4] = {'1', '0', '0', '6'};
char intento[4] = {0, 0, 0, 0};
boolean entrada_pass = false;
boolean habilitado = true;
byte pos = 0;

unsigned long previousMillis = 0;
const long intervalo = 1000;
unsigned long currentMillis = 0;
byte segundos_intento = 11;
byte segundos_inhabilitado = 20;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Bienvenido");

  pinMode(led_hab, OUTPUT);
  pinMode(led_des, OUTPUT);

}


void iniciar() {
    lcd.clear();
    lcd.print("Bienvenido");
    reset_intento();
    entrada_pass = false;
    habilitado = true;
    segundos_intento = 11;
    segundos_inhabilitado = 20;
}


void reset_intento() {
  pos = 0;
  for (int i=0; i<4; i++) {
    intento[i] = 0;
  }  
}


void revisar() {
  int correctos = 0;
  for (int i =0; i<4; i++) {
    if (intento[i] == password[i]) {
      correctos++;
    }    
  }
  if (correctos == 4) {
    habilitado = false;
    lcd.clear();
    lcd.print("Deshabilitado");    
  } else {
    iniciar();
  }

}


void loop() {

  // leds indicadores
  if (habilitado) {
    digitalWrite(led_hab, HIGH);
    digitalWrite(led_des, LOW);
    key = kpad.getKey();
  } else { 
    digitalWrite(led_hab, LOW);
    digitalWrite(led_des, HIGH);

    // contador inhabilitado
    currentMillis = millis();
    lcd.setCursor(0, 1);
    lcd.print(segundos_inhabilitado);
    lcd.print(' ');
    if (currentMillis - previousMillis >= intervalo) {
      previousMillis = currentMillis;
      segundos_inhabilitado -= 1;
    }

    if (segundos_inhabilitado <= 0) {
      iniciar();
    }

    // delay(20000);
    // iniciar();
  }

 // tiempo de entrada
  if (entrada_pass) {
    currentMillis = millis();
    lcd.setCursor(12, 0);
    lcd.print(segundos_intento);
    lcd.print(' ');
    if (currentMillis - previousMillis >= intervalo) {
      previousMillis = currentMillis;
      segundos_intento = segundos_intento - 1;
    }

    if (segundos_intento <= 0) {
      iniciar();
    }
  }

  // entrada
  // key = kpad.getKey();
  
  if (key != NO_KEY) {

    if (key == '*' && entrada_pass == false) {
      lcd.clear();
      lcd.print("Contrasena:");
      entrada_pass = true;
      delay(500);
    } else if (entrada_pass) {
      lcd.setCursor(pos, 1);
      lcd.print('*');
      intento[pos] = key;
      pos += 1;

      delay(300);
      if (pos >= 4) {
        entrada_pass = false;
        revisar();
      }
    }
  }

}
