

#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define  LED  13


AndroidAccessory acc = AndroidAccessory("Anywhere Software",
"ADKDemo",
"Arduino ADK Board demo.",
"1.0",
"http://www.basic4ppc.com",
"1");

boolean connected;



int freeRam()
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}


void setup()
{
  Serial.begin(115200);
  
  pinMode(LED, OUTPUT); 
  digitalWrite(LED, LOW); // use the pin 23 LED as a connected indicator
  connected = false; // flag for last connected state

  // need this delay before acc.powerOn() to avoid "starterror: OSCOKIRQ failed to assert"
  // it lets the PLL in the MAX3421e host USB IC stabilise after reset
  delay(500); 
  acc.powerOn();
  Serial.println("Started");
}


void loop()
{
  static byte count = 0;
  byte msg[64];

  if (acc.isConnected())   
  {
    if (!connected) // one time flag
    {
      connected = true;
      digitalWrite(LED, HIGH);
      Serial.println(F("Connected")); // the F("..") stores the string in ROM instead of precious RAM
      Serial.print(F("Free RAM = ")); // http://jeelabs.org/2011/05/22/atmega-memory-use/
      Serial.println(freeRam());
    }
    int len = acc.read(msg, sizeof(msg), 1);
    if (len > 0)
    {
      acc.write(msg, len);
      for (int i = 0; i <len; i++)
      {
        Serial.print((char)msg[i]);
      }
    }
    len = Serial.available();
    if (len > 0)
    {
      len = Serial.readBytes((char*)msg, sizeof(msg)); // readBytes seems to need a char* not a byte*
      acc.write(msg, len);
    }
  }
  else
  {
    if (connected)
    {
      connected = false;
      digitalWrite(LED, LOW);
      Serial.println(F("Disconnected"));
    }
    delay(10); // no real reason for this, just slows things down a bit
  }
}







