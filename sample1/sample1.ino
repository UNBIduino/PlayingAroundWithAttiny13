const uint8_t uart_rx_pin = 1;


volatile boolean readed = false;
unsigned long curmicros = 0;
unsigned long   CS_Timeout_Millis = 0;
unsigned long   total = 0;
void rxInterrupt()
{
  bool value = digitalRead(PB4);

  if (value) {
    Serial.print(F("High"));
    Serial.print(total);
    Serial.write('\n');
  } else {
    Serial.print(F("LOW"));
    Serial.print(total);
    Serial.write('\n');
  }
  readed = true;
}

void setup()
{
  // Note that any baud rate specified is ignored on the ATtiny13. See header above.
  Serial.begin();
  // Prepare for sleep mode
  //  MCUCR = _BV(SE);
  // Enable Rx pin pullup
  digitalWrite(uart_rx_pin, HIGH);
  // Setup RX interrupt
  attachInterrupt(0, rxInterrupt, LOW);

  float loopTimingFactor = 310;   // determined empirically -  a hack
  CS_Timeout_Millis = (2000 * (float)loopTimingFactor * (float)F_CPU) / 16000000;
  delay(1000);

}
void loop()
{
  //  asm("sleep");
  if (readed) {
    readed = false;
    total = 0;
    detachInterrupt(digitalPinToInterrupt(uart_rx_pin));
    for (uint8_t num = 0; num < 30; num++ ) {
      digitalWrite(uart_rx_pin, LOW);
      pinMode(PB4, INPUT);
      pinMode(PB4, OUTPUT);
      digitalWrite(PB4, LOW);
      delayMicroseconds(10);
      pinMode(PB4, INPUT);
      digitalWrite(uart_rx_pin, HIGH);
      while ( !digitalRead(PB4) && (total < CS_Timeout_Millis) ) {  // while receive pin is LOW AND total is positive value
        total++;
      }
      //    Serial.println("M");
      //    curmicros=micros();
      //    delay(5000);
      //    Serial.println("C");
    }
    digitalWrite(uart_rx_pin, HIGH);
    attachInterrupt(0, rxInterrupt, LOW);

  }
}
