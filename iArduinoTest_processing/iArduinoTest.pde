//-----------------Processing code-----------------


import oscP5.*;        //  Load OSC P5 library
import netP5.*;        //  Load net P5 library
import processing.serial.*;    //  Load serial library


Serial arduinoPort;        //  Set arduinoPort as serial connection
OscP5 oscP5;            //  Set oscP5 as OSC connection

//int redLED = 0;        //  redLED lets us know if the LED is on or off
//int blueLED = 0; 
int [] led = new int [47];    //  Array allows us to add more toggle buttons in TouchOSC

void setup() {
  //println(Serial.list()); 
  size(200,100);        // Processing screen size
  noStroke();            //  We don’t want an outline or Stroke on our graphics
  oscP5 = new OscP5(this,8000);  // Start oscP5, listening for incoming messages at port 8000
  arduinoPort = new Serial(this, Serial.list()[2], 9600);    // Set arduino to 9600 baud
}

void oscEvent(OscMessage theOscMessage) {   //  This runs whenever there is a new OSC message

    String addr = theOscMessage.addrPattern();  //  Creates a string out of the OSC message
    if(addr.indexOf("/1/multipush1/") !=-1){   // Filters out any toggle buttons
      //try {
        //int i = int(addr.charAt(16)) - 0x30; 
        int i = Integer.parseInt(""+addr.charAt(14)+addr.charAt(16));   // returns the ASCII number so convert into a real number by subtracting 0x30
        led[i]  = int(theOscMessage.get(0).floatValue());     //  Puts button value into led[i]
      // Button values can be read by using led[0], led[1], led[2], etc.
      } 
    //catch(NumberFormatException e) {}
    }
//}

void draw() {
  //background(50);        // Sets the background to a dark grey, can be 0-255
  //println(led[11]);
  //String test = "/1/multipush1/1/1";
  //println(test.charAt(14)=='1'); 
  
  String output = ""; 
  for (int i=1; i<=4; i++) {
    for (int j=1; j<=6; j++) {
      if (led[i*10+j] == 0) {
        output = output+"0";
      } else {
        output = output+"1"; 
      }
    }
  }
  
  output = output + '\n';
  print(output); 
  //println(output.charAt(0) == '1'); 
  arduinoPort.write(output); 
  
  //if(led[1] == 0){        //  If led button 1 is off do....                                 r
  //  arduinoPort.write("r");    // Sends the character “r” to Arduino
  //  //redLED = 0;        // Sets redLED color to 0, can be 0-255
  //}
  //if(led[1] == 1){        // If led button 1 is ON do...
  //  arduinoPort.write("R");    // Send the character “R” to Arduino
  //  //redLED = 255;        // Sets redLED color to 255, can be 0-255
  //}
  
  ////fill(redLED,0,0);            // Fill rectangle with redLED amount
  ////ellipse(50, 50, 50, 50);    // Created an ellipse at 50 pixels from the left...
  //              // 50 pixels from the top and a width of 50 and height of 50 pixels
                
  //if(led[2] == 0){        //  If led button 2 is off do....
  // arduinoPort.write("a");    // Sends the character “r” to Arduino
  // //blueLED = 0;        // Sets redLED color to 0, can be 0-255
  //}
  //if(led[2] == 1){        // If led button 2 is ON do...
  // arduinoPort.write("A");    // Send the character “R” to Arduino
  // //blueLED = 255;        // Sets redLED color to 255, can be 0-255
  //}
  
  //fill(0,0,blueLED); 
  //ellipse(150, 50, 50, 50); 
}
//----------------------------------end processing code------------------------------------