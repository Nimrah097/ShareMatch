#include <Servo.h>                // Functions to controll servo motor
#include <SoftwareSerial.h>       // Including SoftwareSerial to create a virtual serial port
SoftwareSerial Bluetooth(0,1);    // Create a SoftwareSerial object Blueooth on pins 0 and 1

#include <LiquidCrystal_I2C.h>    // Interfacing with I2C 
#include <Wire.h>                 // Communication with I2C 
LiquidCrystal_I2C lcd(0x27,16,2); // Create an I2C LCD object with address 0x27, 16 columns, and 2 rows


const int ultrasonicTrigPin1 = 6; // Trig pin for ultrasonic sensor 1
const int ultrasonicEchoPin1 = 7; // Echo pin for ultrasonic sensor 1
const int ultrasonicTrigPin2 = 8; // Trig pin for ultrasonic sensor 2
const int ultrasonicEchoPin2 = 9; // Echo pin for ultrasonic sensor 2

const int servoPin1 = 4;          // Digital pin for player 1 servo motor
const int servoPin2 = 5;          // Digital pin for player 2 servo motor

Servo player1Servo;
Servo player2Servo;


int player1Score = 0;            // Initialize the score for player 1
int player2Score = 0;            // Initialize the score for player 2

unsigned long goalCooldownTime = 0; // Stores the values of the millis() function

void setup() {
  Serial.begin(9600);
 
  pinMode(ultrasonicTrigPin1, OUTPUT);
  pinMode(ultrasonicEchoPin1, INPUT);
  pinMode(ultrasonicTrigPin2, OUTPUT);
  pinMode(ultrasonicEchoPin2, INPUT);

  player1Servo.attach(servoPin1); // Attach player1Servo to the digital pin for controlling the servo motor of Player 1
  player2Servo.attach(servoPin2); // Attach player2Servo to the digital pin for controlling the servo motor of Player 2


  // Initialize LCD
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setBacklight(HIGH);
}

void loop() {

  
  // Rotate player 1 servo continuously
  player1Servo.write(180);
  delay(500);  // Delay rotation for 0.5 seconds
  player1Servo.write(0);
  delay(500);

  // Rotate player 2 servo continuously
  player2Servo.write(180);
  delay(500);  // Delay rotation for 0.5 seconds
  player2Servo.write(0);
  delay(500);

  
  if (detectGoal(ultrasonicTrigPin1, ultrasonicEchoPin1)) {    // ultrasonicTrigPin1 and ultrasonicEchoPin1 are used as parameters 
    if (millis() > goalCooldownTime) {                         // Checks if goalCooldownTime is less than millis
      player1Score++;                                          // player1score is incremented by a value

      //Prints the score for player 1 in serial monitor
      Serial.println("Goal for Player 1!");                    
      Serial.print("Player 1 Score: ");
      Serial.println(player1Score);
      
      goalCooldownTime = millis() + 5000;                    // Set a 5-second cooldown
      updateLCD();                                           // Function called to update score values on LCD
    }
  }

  if (detectGoal(ultrasonicTrigPin2, ultrasonicEchoPin2)) {  // ultrasonicTrigPin2 and ultrasonicEchoPin2 are used as parameters
    if (millis() > goalCooldownTime) {                       // Checks if goalCooldownTime is less than millis
      player2Score++;                                        // player2score is incremented by a value

      //Prints the score for player 2 in serial monitor
      Serial.println("Goal for Player 2!");
      Serial.print("Player 2 Score: ");
      Serial.println(player2Score);
     
      goalCooldownTime = millis() + 5000;                   // Set a 5-second cooldown
      updateLCD();                                          // Function called to update score values on LCD
    }
  }
  delay(100);                                               // Delays the entire function to 0.1 seconds
  
  // Check for game end
  if (player1Score >= 5) {                                  // Checks if player 1 has scored 5 or more goals
    Serial.println("PLayer 1 wins!!!");
    while (true) {
      // Endless loop to stop further game processing
    }
  }
  if (player2Score >= 5) {                                  // Checks if player 2 has scored 5 or more goals
    Serial.println("PLayer 2 wins!!!");
    while (true) {
      // Endless loop to stop further game processing
    }
  }
}


// Create a function to detect a goal using an ultrasonic sensor
bool detectGoal(int trigPin, int echoPin) {   
  
  long duration;   // Define a variable that stores duration to calculate distance  
  int distance;    // Define a variable distance to later determine the ball distance 

  digitalWrite(trigPin, LOW);   // Clears the trigPin
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);   // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;     // Calculating the distance in cm
  return (distance < 7);               // Distance less than 7cm is returned when the function is called
}


//Create a function to update the LCD to display players' scores 
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);     // Sets the cursor to the first column and first row
  lcd.print("Score: ");
  lcd.print(player2Score);
  lcd.print(" - ");
  lcd.print(player1Score);
}
