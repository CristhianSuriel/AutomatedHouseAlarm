#define light 13
#define buttonPin 10

int alarmState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(light, OUTPUT);
}

void loop() {
  checkAlarm();
  if (alarmState == HIGH) {
    digitalWrite (light, HIGH);
  }
  else {
    digitalWrite (light, LOW);
  }
}

void checkAlarm () {
  //Checks if the alarm is activated or not
  alarmState = digitalRead(buttonPin);
  Serial.println (alarmState);
  if (buttonPin == HIGH) {
    alarmState == HIGH;
    delay(1);
  }
  else {
    alarmState == LOW;
    delay(1);
  }
}
