
#define TINY_ADC_PB2 0x01
#define TINY_ADC_PB3 0x03
#define TINY_ADC_PB4 0x02
#define TINY_ADC_PB5 0x00
#define CHECK_INTERVAL 200
#define BOOT_SETTING_CALIB_TIME 15000

const uint8_t uart_rx_pin = 1;
unsigned long value = 0;
unsigned long max_value = 0;
unsigned long counter = 0;
boolean is_caliberated = false;
boolean keystate = false;
unsigned long turnofftime = 0;

unsigned long setup_finish_time = 0;
void setup()
{
  Serial.begin();
  pinMode(PB4, OUTPUT);
  digitalWrite(PB4, HIGH);
  pinMode(PB1, OUTPUT);
  digitalWrite(PB1, HIGH);
  delay(3000);
  setup_finish_time = millis();
}
unsigned long mili = 0;
void loop()
{
  unsigned int r_data = analogRead(TINY_ADC_PB4);
  if (r_data >= 1016) {
    return;
  }
  value = value + r_data;
  counter++;
  unsigned long cur = millis();
  if (cur - mili > CHECK_INTERVAL) {
    mili = cur;
    value = value / counter;
    //    Serial.println(max_value);
    //    Serial.println(value);

    if (max_value < value && (cur - setup_finish_time) < BOOT_SETTING_CALIB_TIME ) {
      max_value = value;
    } else if ((cur - setup_finish_time) > BOOT_SETTING_CALIB_TIME ) {
      if (!is_caliberated) {
        is_caliberated = true;
        max_value = (max_value * 995) / 1000;
      }
    }
    if (is_caliberated) {
      //      if (value < max_value && keystate == false) {
      //        //        Serial.println("O");
      //        keystate = true;
      //        //        turnofftime = cur / 1000 + 30; //1000*60*10/
      //        turnofftime = cur / 1000 + 600; //1000*60*10
      //      }
      //      if (value > max_value) {
      //        keystate = false;
      //        turnofftime = 0; /// turn off when the key is off
      //        //        Serial.println("F");
      //      }
    }
    //        Serial.println(max_value);
    Serial.println(value);
    value = 0;
    counter = 0;
  }
  if (cur / 1000 > turnofftime) {
    digitalWrite(PB1, HIGH);
  } else {
    digitalWrite(PB1, LOW);
  }
}
