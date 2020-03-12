#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String password = "369#";
String passwordAttempt = "";
Servo myServo;

void setup(){
  Serial.begin(9600);
  myServo.attach(9);
}
  
void loop(){ 
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    passwordAttempt += String(key);
  }
  if (passwordAttempt.equals(password)) {
    Serial.println("You did it!");
    myServo.write(90); //set servo to midpoint (open door)
    delay (3000);
    passwordAttempt = "";
  }
  else  {
    myServo.write(0); //set servo to 0 (close door)
    delay(1);
  }
}
