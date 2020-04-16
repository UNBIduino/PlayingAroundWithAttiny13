const uint8_t uart_rx_pin = 1;

void rxInterrupt()
{
  Serial.print(F("Delta: 0xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"));
  Serial.write('\n');
}

void setup()
{
  // Note that any baud rate specified is ignored on the ATtiny13. See header above.
  Serial.begin();

  // Prepare for sleep mode
  MCUCR = _BV(SE);

  // Enable Rx pin pullup
  digitalWrite(uart_rx_pin, HIGH);

  // Setup RX interrupt
  attachInterrupt(0, rxInterrupt, LOW);
  delay(1000);

}
void loop()
{
  asm("sleep");
}
