// =====================================================================================================================
// Name: Tinkerkit_Braccio_Robot_V1
// Description: This program allows control of a Braccio robotic arm through serial communication.
// Target: Arduino Uno
// Compiler: Arduino IDE
// Usage: Control the Braccio robot using Python
// Restriction(s): None.
// History: 7/05/2024 | E. Zoukou / C. Courtemanche / K. Niamba / Creation;
//          1/28/2025 | K. Niamba / Modification ---> Documentation translation (FR to ENG);
// =====================================================================================================================

// =====================================================================================================================
// Inclusion of files
// =====================================================================================================================
#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

// --------------------------------------------------
// Block for retrieving << String >> values from C Lion for the Arduino IDE
// --------------------------------------------------
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;             
      strIndex[0] = strIndex[1] + 1;       
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
} 

// --------------------------------------------------
// Initialization block
// --------------------------------------------------
void setup() {
  Braccio.begin();
  Serial.begin(9600);
} 

// =====================================================================================================================
// Main program #2
// =====================================================================================================================
void loop() { 
  if (Serial.available() > 0) {

    // --------------------------------------------------
    // Block for splitting the string
    // --------------------------------------------------
    String reception = Serial.readStringUntil('\n');
    String stringV = getValue(reception, ':', 0);
    String stringM1 = getValue(reception, ':', 1);
    String stringM2 = getValue(reception, ':', 2);
    String stringM3 = getValue(reception, ':', 3);
    String stringM4 = getValue(reception, ':', 4);
    String stringM5 = getValue(reception, ':', 5);
    String stringM6 = getValue(reception, ':', 6);
    
    // --------------------------------------------------
    // Block for converting strings to ints
    // --------------------------------------------------
    int V = stringV.toInt();
    int M1 = stringM1.toInt();
    int M2 = stringM2.toInt();
    int M3 = stringM3.toInt();
    int M4 = stringM4.toInt();
    int M5 = stringM5.toInt();
    int M6 = stringM6.toInt();
    
    // --------------------------------------------------
    // Block for speed and movements of the Braccio servo motors
    // --------------------------------------------------
    Braccio.ServoMovement(V, M1, M2, M3, M4, M5, M6);      // Values entered in C Lion
    delay(1000);
    
    Braccio.ServoMovement(V, M1, M2, M3, M4, M5, 73);      // The gripper is closed
    delay(1000);
    
    Braccio.ServoMovement(V, M1, M2, 90, 90, M5, 73);      // The arm is raised
    delay(1000);
    
    Braccio.ServoMovement(V, 180, M2, 90, 90, M5, 73);     // The base makes a half turn and the gripper is closed
    delay(1000);
    
    Braccio.ServoMovement(V, 180, M2, M3, M4, M5, 73);     // The base stays the same and the gripper is closed
    delay(1000);
    
    Braccio.ServoMovement(V, 180, M2, M3, M4, M5, 10);     // The base stays the same and the gripper is open
    delay(1000);

    // --------------------------------------------------
    // Block for returning to the initial position 
    // --------------------------------------------------
    Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 73);     // Return to the initial position
  } 
}