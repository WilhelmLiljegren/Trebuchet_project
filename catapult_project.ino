/*
* Name: Semi automatic trebuchet
* Author: Wilhelm Liljegren
* Date: 2025-05-08
* Description: This project is a trebuchet and catapult hybrid which can change the facing direction within 180 degrees
* and the drawback can be adjusted.
*/

// Include libraries for motor, servo, and NeoPixel control
#include <Stepper.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// Define constants for the number of NeoPixels and steps for stepper motor
#define NUMPIXELS 24
#define STEPS 100

// Pin assignments
int Neopin = 7;  // NeoPixel pin
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(24, 7, NEO_GRB + NEO_KHZ800);  // Initialize NeoPixel object
Stepper stepper(STEPS, 1, 2, 3, 4);  // Initialize Stepper motor with 4 pins for control

#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Define variables for timing and button states
int time;  // Time variable used for controlling stepper movement
int btnpin = 8;  // Pin for the button
int servopin = 10;  // Pin for controlling the servo
bool fire;  // Boolean to indicate if firing is active
int l1 = 13, l2 = 12, l3 = 11, l4 = 6;  // Pins for controlling LEDs
Servo myservo; 
int potentiometer = A0;  // Pin for potentiometer

void setup() {
  Serial.begin(9600);             // Start serial communication for debugging
  pinMode(potentiometer, INPUT);  // Set the potentiometer pin as input
  myservo.attach(10);  // Attach the servo motor to pin 10
  pixels.begin();  // Initialize NeoPixel
  stepper.setSpeed(250);  // Set stepper motor speed
  time = 0;  // Initialize time variable
}

void loop() {
  // Read potentiometer value to control the firing angle
  int sensor_value = analogRead(potentiometer);  
  
  // Map the potentiometer value to a range from 0 to 180 (for servo movement)
  int pos = map(sensor_value, 0, 1023, 0, 180);  
  int value = map(sensor_value, 0, 1023, 0, 12);  // Map the value for NeoPixel control
  
  // Clear previous NeoPixel pixels and set the new pixel based on the potentiometer value
  pixels.clear();
  pixels.setPixelColor(value, pixels.Color(0, 255, 0));  // Set color to green 
  pixels.show();  // Update the NeoPixel display
  delay(50);  // Short delay to allow the visual to update

  // Check if the button is pressed to initiate firing
  if (digitalRead(btnpin)) {
    fire = true;  // Set the fire to true
    
    // Wait for button to be released to avoid multiple triggers
    while (digitalRead(btnpin)) {
      delay(50);
    }
    
    // If button is released, adjust the servo position based on the potentiometer value
    if (digitalRead(btnpin) == 0) {
      myservo.write(pos);  // Move servo to the calculated position
      pixels.clear();  // Clear NeoPixels
      pixels.setPixelColor(value, pixels.Color(255, 0, 0));  // Red for firing
      pixels.show();  // Update NeoPixel display
      delay(10);
    }
  }

  // If firing is active, begin the launch sequence
  while (fire == true) {
    // Read potentiometer value and map it to determine firing power
    int worth = analogRead(potentiometer);
    int lightvalue = map(worth, 0, 1023, 1, 5);  // Map value to control power level (1-5)

    // Control the LEDs for different levels of power
    if (lightvalue == 1) {
      digitalWrite(l4, HIGH);
      delay(10);
      digitalWrite(l3, LOW);
      delay(10);
      digitalWrite(l2, LOW);
      delay(10);
      digitalWrite(l1, LOW);

      // If the button is pressed and lightvalue is 1, start the first drag
      if ((lightvalue == 1) && (digitalRead(btnpin))) {
        time = 0;  // Reset time for drag
        drag1();  // Perform drag1
      }
    }
    if (lightvalue == 2) {
      digitalWrite(l3, HIGH);
      delay(10);
      digitalWrite(l4, HIGH);
      delay(10);
      digitalWrite(l2, LOW);
      delay(10);
      digitalWrite(l1, LOW);
      if ((lightvalue == 2) && (digitalRead(btnpin))) {
        time = 0;  // Reset time for drag
        drag2();  // Perform drag2
      }
    }
    if (lightvalue == 3) {
      digitalWrite(l2, HIGH);
      delay(10);
      digitalWrite(l4, HIGH);
      delay(10);
      digitalWrite(l3, HIGH);
      delay(10);
      digitalWrite(l1, LOW);
      if ((lightvalue == 3) && (digitalRead(btnpin))) {
        time = 0;  // Reset time for drag
        drag3();  // Perform drag3
      }
    }
    if (lightvalue == 4) {
      digitalWrite(l1, HIGH);
      delay(10);
      digitalWrite(l4, HIGH);
      delay(10);
      digitalWrite(l3, HIGH);
      delay(10);
      digitalWrite(l2, HIGH);
      if ((lightvalue == 4) && (digitalRead(btnpin))) {
        time = 0;  // Reset time for drag
        drag4();  // Perform drag4
      }
    }
  }
}
//Functions for the different amounts of drawback
// Function for the first level of drag, where the trebuchet is launched
void drag1() {
  while (time < 200) {  // Run 200 times
    stepper.step(STEPS);  // Move stepper motor by the defined steps
    delay(10);  // Short delay between steps
    time += 1;  // Increment time for each step
  }
}

// Function for the second level of drag, where the trebuchet is launched
void drag2() {
  while (time < 300) {  // Run 300 times
    stepper.step(STEPS);  // Move stepper motor by the defined steps
    delay(10);  // Short delay between steps
    time += 1;  // Increment time for each step
  }
}

// Function for the third level of drag, where the trebuchet is launched
void drag3() {
  while (time < 400) {  // Run 400 times
    stepper.step(STEPS);  // Move stepper motor by the defined steps
    delay(10);  // Short delay between steps
    time += 1;  // Increment time for each step
  }
}

// Function for the fourth level of drag, where the trebuchet is launched
void drag4() {
  while (time < 500) {  // Run 500 times
    stepper.step(STEPS);  // Move stepper motor by the defined steps
    delay(10);  // Short delay between steps
    time += 1;  // Increment time for each step
  }
}