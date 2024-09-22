// Jonathan Mehmannavaz ©
// How to turn on the light

void setup() {

  // DDRB or value of PB5 at one. DDRX : data direction register
  DDRB |= (1 << PB3);
}

void loop() {

// PortB or value of PB5 at one.
 PORTB |= (1 << PD3);
_delay_ms(1000);

// PortB and value of PB5 at zero.
 PORTB &= ~(1 << PD3);
_delay_ms(1000);

}
