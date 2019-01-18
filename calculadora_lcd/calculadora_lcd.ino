//Funcional

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
  {{'1', '2', '3', '+'},
   {'4', '5', '6', '-'},
   {'7', '8', '9', '/'},
   {'C', '0', '=', '*'}};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};
Keypad kpad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char key;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Calculadora");
  delay(2000);

}

boolean anterior = false;
boolean valor1 = false;
boolean valor2 = false;
boolean nuevoValor2 = false;
String num1, num2;
double resultado;
double numero1 = 0;
double numero2 = 0;
char operador;
boolean iniciando = true;

void loop(){
  // animacion inicio
  if (iniciando) {
    for (int posCont = 0; posCont < 10; posCont++) {
      lcd.scrollDisplayLeft();
      delay(150);
    }    
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.cursor();
    iniciando = false;    
  }
  
  key = kpad.getKey();

  if (key != NO_KEY && (key >= '0' && key <= '9'))
  {
    if (valor1 != true) // asignar valor 1
    {
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0);
      lcd.print(num1);
      numero1 = numero1 * 10 + (key - '0'); // obtener el valor numerico restando valores ASCII
    }
    else if(valor2 != true) // asignar valor 2
    {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      valor2 = true;
      numero2 = numero2 * 10 + (key - '0');
    }
    // asignar valor 2 para realizar una operacion con el resultado anterior
    if (anterior == true && nuevoValor2 == true) 
    {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      numero2 = numero2 * 10 + (key - '0');
    }
  }
  // al ingresar un operador se activa la bandera del valor1
  else if (valor1 == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'))
  {
    if (valor1 == false)
    {
      valor1 = true;
      operador = key;
      lcd.setCursor(15,0);
      lcd.print(operador);
    }
    
  }
  // si hay resultado anterior se pueden realizar operaciones
  else if (anterior == true && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'))
  {
      operador = key;
      lcd.setCursor(15,0);
      lcd.print(operador);
      nuevoValor2 = true;
  }
  // si hay segundo valor puede mostrar el resultado
  else if (valor2 == true && key != NO_KEY && key == '=')
  {

    if (operador == '+') {
      resultado = numero1 + numero2;
    }
    else if (operador == '-') {
      resultado = numero1 - numero2;
    }
    else if (operador == '*') {
      resultado = numero1 * numero2;
    }
    else if (operador == '/') {
      resultado = numero1 / numero2;
    }

    lcd.clear();
    num1 = String(resultado);
    numero1 = resultado;
    lcd.setCursor(15 - num1.length(), 0);
    lcd.print(num1);
    num2 = "";
    numero2 = 0;
    resultado = 0;
    anterior = true;
    nuevoValor2 = false;

  }
  // reiniciar los valores
  else if (key != NO_KEY && key == 'C')
  {
    lcd.clear();
    lcd.setCursor(15,0);
    valor1 = false;
    valor2 = false;
    num1 = "";
    num2 = "";
    resultado = 0;
    operador = ' ';
    anterior = false;
    nuevoValor2 = false;
    numero1 = 0;
    numero2 = 0;

  }
}

