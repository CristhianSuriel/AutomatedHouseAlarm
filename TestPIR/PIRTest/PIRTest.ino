#define light 12
#define PIR 7

int val =0;

void setup() {
  Serial.begin(9600);
  pinMode(light, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  val = digitalRead(PIR);
  Serial.println (val);
  
  if (val == HIGH) {
    digitalWrite(light, HIGH);
  }
  delay (1000);
  if (val == LOW) {
    digitalWrite(light, LOW);
  } 
  delay(1000);
}
