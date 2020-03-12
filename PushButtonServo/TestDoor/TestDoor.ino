#include <Servo.h>

const int buttonPin = 2; // push button pin

int buttonState = 0; //variable for the push button status
Servo myservo;

void setup() {
  pinMode (buttonPin, INPUT);
  myservo.attach(9); //pin for the servo

}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    myservo.write(90); // set servo to midpoint (open door)
    delay (1); //leave the door open for 2 seconds
  }
  else {
    myservo.write(0); //servo position is 0 or the door is closed
    delay(3000); //precausion delay
  }

}
