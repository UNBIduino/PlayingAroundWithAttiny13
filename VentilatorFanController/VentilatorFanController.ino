
#define TINY_ADC_PB2 0x01
#define TINY_ADC_PB3 0x03
#define TINY_ADC_PB4 0x02
#define TINY_ADC_PB5 0x00
#define CHECK_INTERVAL 4000
#define BOOT_SETTING_CALIB_TIME 15000
#define COUNTER 5000

unsigned long value = 0;
unsigned long ref_value = 0;
unsigned long counter = 0;
boolean is_caliberated = false;
boolean keystate = false;
unsigned long turnofftime = 0;

void setup()
{
  Serial.begin();
  pinMode(PB4, OUTPUT);
  digitalWrite(PB4, HIGH);
  pinMode(PB1, OUTPUT);
  digitalWrite(PB1, HIGH);
}
void loop()
{
  unsigned long cur = millis();
  if (cur / 1000 > turnofftime) {
    digitalWrite(PB1, HIGH);
  } else {
    if (is_caliberated) {
      digitalWrite(PB1, LOW);
    }
  }
  unsigned int r_data = 1023 - analogRead(TINY_ADC_PB4);
  value = value + r_data;
  counter++;
  if (counter > COUNTER && is_caliberated) {
    if (value > ref_value && keystate == false) {
      //        Serial.println("O");
      keystate = true;
      turnofftime = cur / 1000 + 30; //1000*60*10/
      //        turnofftime = cur / 1000 + 600; //1000*60*10
    }
    if (value < ref_value) {
      keystate = false;
      turnofftime = 0; /// turn off when the key is off
      //        Serial.println("F");
    }
    Serial.println(ref_value);
    Serial.println(value);
    counter = 0;
    value = 0;
  }
  if (!is_caliberated) {
    if (counter > 50000) {
      ref_value = (value * 13) / 100;
      is_caliberated = true;
      counter = 0;
      value = 0;
    }
  }
  //  Serial.println(counter);
}
