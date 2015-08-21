#include <OneWire.h>

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8


OneWire  ds(2);  // on pin 2 (a 4.7K resistor is necessary) between white and red vcc

// create an instance of the library
TFT screen = TFT(cs, dc, rst);

// char array to print to the screen
char sensorPrintout[6];
char celsiusPrint[6];
char fahrenheitPrint[6];

void setup(void) {
  // Put this line at the beginning of every sketch that uses the GLCD:
  screen.begin();

  // clear the screen with a black background
  screen.background(0, 0, 0);

  // write the static text to the screen
  // set the font color to white
  screen.stroke(255, 0, 0);
  // set the font size
  screen.setTextSize(3);
  // write the text to the top left corner of the screen
  screen.text("   POOL", 0, 0);
  screen.line(0, 25, 255, 25);
  screen.setTextSize(2);
  screen.text(" temperature     ", 0, 30);
  screen.line(0, 50, 255, 50);
  // ste the font size very large for the loop
  //screen.stroke(0, 0, 0);
  screen.setTextSize(3);

  
  Serial.begin(9600);
}


void loop(void) 
{
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  //Data = 1 F5 1 4B 46 7F FF B 10 EA  CRC=EA
  // We are using Chip = DS18B20 

  ds.search(addr);
  type_s =0;
  
  ds.reset(); 
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
   
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  
  //FOR ONEWIRE DEBUG
  /*
  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println(); 
  */
  
  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;

  
  //FOR SERIAL DEBUG
  /* 
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
  */
  
  //test screen
  // Read the value of the sensor on A0
  String TempC = String(celsius);
  String TempF = String(fahrenheit);

  // convert the reading to a char array
  TempC.toCharArray(celsiusPrint, 6);
  TempF.toCharArray(fahrenheitPrint, 6);

  // set the font color
  screen.stroke(255, 255, 255);
  // print the sensor value
  screen.text(celsiusPrint, 0, 60);
    screen.text(" C ", 90, 60);
  screen.text(fahrenheitPrint, 0, 100);
  screen.text(" F ", 90, 100);
  // wait for a moment
  delay(250);
  // erase the text you just wrote
  screen.stroke(0, 0, 0);
  screen.text(celsiusPrint, 0, 60);
  screen.text(fahrenheitPrint, 0, 100);

  
}
