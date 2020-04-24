/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. A0 is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin A0 as an output.
  pinMode(PB1, OUTPUT);
  pinMode(PB4, OUTPUT);
  pinMode(PB0, OUTPUT);
  digitalWrite(PB0, HIGH);   // turn the LED on (HIGH is the voltage level)
  pinMode(PB1, OUTPUT);
  digitalWrite(PB1, HIGH);   // turn the LED on (HIGH is the voltage level)
  pinMode(PB0, INPUT);
  pinMode(PB1, INPUT);
}
void(* resetFunc) (void) = 0; //declare reset function @ address 0
// the loop function runs over and over again forever
bool willbuzzer = false;
void loop() {
  if (!willbuzzer) {
    if (digitalRead(PB1) == HIGH) {
      willbuzzer = true;
    }
  }

  while (willbuzzer) {
    bool state_m = digitalRead(PB0);
    if (state_m == LOW) {
      resetFunc();
    }
    buzzer();
  }
}

unsigned long mil = 0;
bool buz_state = false;
unsigned long _time = 0;
void buzzer() {
  unsigned long cur = millis();
  if (cur - mil > _time) {
    mil = cur;
    if (buz_state) {
      noTone(PB4);
      digitalWrite(PB4, LOW);
      tone(PB4, 600);
      _time = 300;
    } else {
      noTone(PB4);
      digitalWrite(PB4, LOW);
      _time = 1000;
    }
    buz_state = !buz_state;
  }
}
