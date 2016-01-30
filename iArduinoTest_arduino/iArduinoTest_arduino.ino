#include "pitches.h"

int sensors[4] = {A15, A14, A13, A12};
int notes[4][7] = { {NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C4, NOTE_CS4, NOTE_G4},
{NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_C4},
{NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_E4},
{NOTE_AS4, NOTE_B4, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_A4} }; 

char inChar = -1; // where to store the character read
int noteDuration = 100;
int speaker = 9;
int threshold = 100;

char inData[4][6];
boolean openString[4];
boolean stringPlayed[4];

void setup() {
  pinMode(speaker, OUTPUT); 
  for (int string = 0; string < 4; string++) {
    pinMode(sensors[string], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    //determines which frets are pressed
    int count = 0;
    while(1) {
      inChar = Serial.read();
      if (count == 24) break;
      int string = count/6;
      int fret = count%6;
      inData[string][fret] = inChar;
      count++;
    }
    count = 0;
    
    for (int string = 0; string < 4; string++) {
      // determines which strings are open
      openString[string] = isStringOpen(string);
      // determines which strings should be played
      stringPlayed[string] = laserBroken(sensors[string]);
    }
    
    // play notes here based on inData and stringPlayed
    playNotes();
  } else {
    delay(50);
    //noTone(speaker);
  }
}

//tone(speaker, notePlaying, durationOfNote)
void playNotes() {
  for (int string = 0; string < 4; string++) {
    if (stringPlayed[string]) {
      if (openString[string]) {
        tone(speaker, notes[string][6]);
        //tone(speaker, notes[string][6], noteDuration);
      } else {
        //play the note of the lowest fret pressed, i.e. highest index in the row
        int fret = lowestFretPressed(string);
        tone(speaker, notes[string][fret]);
        //tone(speaker, notes[string][fret], noteDuration);
      }
      //delay(noteDuration);
      //noTone(speaker);
    }
  }
}

// precondition: assumes string is not open
int lowestFretPressed(int string) {
  for (int fret = 5; fret >= 0; fret--) {
    if (inData[string][fret] == '1') {
      return fret;
    }
  }
  return -1;
}

boolean isStringOpen(int string) {
  for (int fret = 0; fret < 6; fret++) {
    if (inData[string][fret] == '1') {
      return false;
    }
  }
  return true;
}

// returns true if there is no light, beam is broken
boolean laserBroken(int sensorNum) {
  return analogRead(sensorNum) < threshold;
}
