/**************************************************************************/
/*!
    @file     Adafruit_MMA8451.h
    @author   K. Townsend (Adafruit Industries)
    @license  BSD (see license.txt)

    This is an example for the Adafruit MMA8451 Accel breakout board
    ----> https://www.adafruit.com/products/2019

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#define RED 0xFF0000
#define WHITE 0xFFFFF
#define RED 0x0000FF
#define PURPLE 0x8B008B
// Which pin on the Arduino is connected to the NeoPixels?
#define NEOPIN         6 
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  Serial.begin(9600);
  Serial.println("Adafruit MMA8451 test!");
  if (! mma.begin()) {
    Serial.println("Failed to start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);
  
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");  
  pixels.begin();           //start neopixels
}

void loop() {

 sensors_event_t event; 
 mma.getEvent(&event);
 if (event.acceleration.y < -3.0) { 
    for (int j=0; j<10; j++) {
      for(int i=0;i<NUMPIXELS;i++){   
         pixels.setPixelColor(i, pixels.Color(255,0,0)); // Turn on neopixels
         pixels.show(); 
         delay (50);
      }
      for(int i=0;i<NUMPIXELS;i++){   
         pixels.setPixelColor(i, pixels.Color(0,0,0)); // Turn on neopixels
         pixels.show(); 
         delay (50); 
      }
 }
    Serial.print("Stop: \t"); Serial.println(event.acceleration.y);
 }
 else {
  /* Display the results (acceleration is measured in m/s^2) */
    for(int i=0;i<NUMPIXELS;i++){   
       pixels.setPixelColor(i, pixels.Color(0,0,0)); // Turn on neopixels
    }
    //Serial.print("Y: \t"); Serial.println(event.acceleration.y);
    pixels.setPixelColor(0, pixels.Color(0,0,0)); // Turn off neopixels.
    pixels.show(); 
    delay(50);
 }
 }
