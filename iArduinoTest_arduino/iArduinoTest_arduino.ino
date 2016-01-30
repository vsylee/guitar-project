#include "pitches.h"

int threshold = 100; 
int sensor1 = A15; 
int sensor2 = A14;
int sensor3 = A13; 
int sensor4 = A12;  

int notes[4][7] = { {NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C4, NOTE_CS4, NOTE_G4},
{NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_C4},
{NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_E4},
{NOTE_AS4, NOTE_B4, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_A4} }; 

  char inChar = -1; // where to store the character read
  char inData[4][6];
  byte index = 0; 

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8};

char message = -1; 
int speaker = 9; 

void setup() {
  // put your setup code here, to run once:
  pinMode(speaker, OUTPUT); 
  pinMode(sensor1,INPUT); 
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int count = 0;
    while(1) {
      inChar = Serial.read();
      if (count == 24) break;
      int string = count/6;
      int fret = count%6;
      inData[string][fret] = inChar;
      output += inChar;
      count++;
    }
    count = 0;
    // play notes here based on inData
  } else {
    delay(1000);
    noTone(speaker);
  }
}

//int buttonPressed(int row) { 
//  
//  while (Serial.available() > 0) {
//
//    if (index < 6) {
//      inChar = Serial.read(); 
//      inData[index] = inChar; 
//      index++; 
////      inData[index] = '\0'; 
//    } 
//    
//    else if (index == 6) {
//      boolean butPressed = false; 
//      for (int i = 0; i<6; i++) {
//        if (inData[i] == '1') {
//          Serial.println(i); 
//          butPressed = true; 
//          for (int i = 0; i<6; i++) {
//            inData[i] = 0; 
//          }
//          index = 0; 
//          return notes[row-1][i]; 
//        }
//      }
//      //if (butPressed == false) {
//      for (int i = 0; i<6; i++) {
//        inData[i] = 0; 
//      }
//      index = 0; 
//      return notes[row-1][6]; 
//      //}
//    }
////    Serial.println(inData[0]=='1'); 
//    
//    return -1; 
//    
////    for (byte i = 0; i < 6; i++) {
////      inChar = Serial.read(); 
////      if (inChar == '1') {
////        Serial.println(i); 
////        butPressed = true;
////        return notes[row-1][i];
////      }
////    }
////    if (butPressed == false) {
////      return notes[row-1][6]; // return the default note
////    }
//  }
//}

//boolean laserBroken(int sensorNum) {
////  return analogRead(sensorNum < threshold); 
//  if (analogRead(sensorNum) < threshold) { // no light, broken beam
//    return true; 
//  }
//  return false; 
//}
      
  // put your main code here, to run repeatedly:
  //**if (Serial.available()) { 
//    message = Serial.read(); 
//    Serial.println(message); 

//    if (laserBroken(sensor1)) { // string 1 is being played 
//      Serial.println(buttonPressed(1)); 
      //**if (buttonPressed(1) != -1) {
      //**  tone(speaker, buttonPressed(1), 100); 
      //**}
//    }
//
//    if (laserBroken(sensor2)) {
//      tone(speaker, buttonPressed(2), 100); 
//    }
    
//    if (message == 'R') { // if button "G#/Ab" is pressed 
//        tone(speaker, NOTE_C2, 100); 
//    } 
//    if (message == 'A') { // if button next to it is pressed
//      tone(speaker, NOTE_F3, 100); 
//    }
    //**else {
//      delay(1000); 
//      noTone(speaker);   
    //**}
//  }
//}

