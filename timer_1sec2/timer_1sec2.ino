http://fabacademy.org/archives/content/tutorials/09_Embedded_Programming/1sec/index.htm


int en = 0; // valor para enviar al pin, encender 1 apagar 0
int pin = 13;
void setup() {
  pinMode(13, OUTPUT);
  // resetear la configuracion timers
  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1B |= (1 << WGM12); // modo clear timer on compare match en timer

  TIMSK1 |= (1 << OCIE1A); // habilitar interrupt CTC

  // valor a comparar
  OCR1A = 15624; // 16Mz/1024=15.625khz velocidad de cuenta con prescaler 1024
                // 65535/15.625khz=4.19424sec overflow de contador de 16 bits
                // 65535/4.19424sec=15625  valor cuando paso 1 segundo
  // prescaler 1024
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);

}

ISR(TIMER1_COMPA_vect) { // accion de la interrupcion
  en = !en;
  digitalWrite(pin, en);

}
void loop() {

}
