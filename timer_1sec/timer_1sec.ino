int z = 0;

void setup() {
  pinMode(13, OUTPUT);
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<CS12); // prescaler /256
  TIMSK1 |= (1<<TOIE1); // timer overflow
  TCNT1 = 3036;
   
}

  ISR(TIMER1_OVF_vect){
    TCNT1 = 3036;
    z = !z;
  }

void loop() {
  digitalWrite(13, z);
}
