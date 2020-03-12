#include <Servo.h> //include servo library
#include <Keypad.h> //includes the library for the keypad
#include "pitches.h" //includes pitches header file


#define light 13 // assign the keyword light to pin 13
#define spkPin 12 // assign the keyword spkPin to pin 12
#define PIR 11 // assign the keyword PIR to pin 11
#define buttonPin 10 // assign keyword buttonPin to pin 10
#define servoPin 9  //pin for the servo motor


int alarmState = false; //Variable for the push button status to open door
int valPIR = 0; //Value the PIR senses
const byte ROWS = 4; //4 rows for the keypad
const byte COLS = 3; //3 columns for the keypad
String password = "369#"; //password to open door
String passwordAttempt = ""; //empty string for the password attempt

//notes in the melody
int melody[] = {
  NOTE_C6, 0, NOTE_C6
};
//the duration of each note: 4 = quarter note, 8 = eighth note, etc...
int noteDurations[] = {
  2, 4, 2
};
//Keyboard layout
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pins of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pins of the keypad

Servo myServo;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/////////////////Setup Code////////////////////////////////////

void setup() {
  Serial.begin(9600);
  pinMode (buttonPin, INPUT);
  pinMode (PIR, INPUT);
  pinMode (light, OUTPUT);
  myServo.attach(servoPin);
}

////////////////////Main Code//////////////////////////////////

void loop() {
  doorCommand(); //This function checks a password to open the door
  checkAlarm(); //This function checks if the alarm is set or not
  valPIR = digitalRead(PIR); //reads the value the PIR is receiving
  Serial.println (valPIR); //prints the value to the serial monitor
  Serial.println (alarmState);
  //if the PIR detects someone turn the lights on
  if (valPIR == HIGH) {
    digitalWrite (light, HIGH);
    //if the alarm is set it will sound
    while (alarmState == 1) {
      alarmOn();
      checkAlarm();
    }
  }
  //if the PIR doesn't detect someone turn the lights off
  if (valPIR == LOW)
    digitalWrite (light, LOW);
}

//////////////////Functions///////////////////////////////////////////

void doorCommand() {
  char key = keypad.getKey(); //get the character from keypad
  if (key) {
    //Serial.println(key);
    passwordAttempt += String(key); //add character to string attempt
  }
  if (passwordAttempt.equals(password)) {
    myServo.write(90); //set servo to midpoint (open door)
    delay (3000); //precaution delay
    passwordAttempt = "";
  }
  else {
    myServo.write(0); // servo position is 0 (door closed)
    delay (1); //door open delay
  }
}

void alarmOn () {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 3; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(spkPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(spkPin);
  }
  delay (1000);
}

void checkAlarm () {
  //Checks if the alarm is activated or not
  if (digitalRead(buttonPin) == true) {
    alarmState = !alarmState;
  }
  while (digitalRead(buttonPin) == true);
  delay(50);
}
