#define TIME 20 //sec
void setup() {
  // put your setup code here, to run once:

  pinMode(PB0, INPUT );
  pinMode(PB4, OUTPUT);
}

unsigned long turnofftime = 0;
boolean willturnon = false;
void loop() {
  // put your main code here, to run repeatedly:

  unsigned long cur = millis() / 1000;
  boolean pinstate = digitalRead(PB0);
  if (!pinstate) {
    turnofftime = cur + TIME;
    willturnon = true;
  }

  if (turnofftime - cur < 3) {
    digitalWrite(PB4, HIGH);
  } else {
    if (willturnon) {
      digitalWrite(PB4, LOW);
      willturnon = false;
    }
  }

}
