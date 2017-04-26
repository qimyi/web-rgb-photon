/*
 * Project Web-RGB
 * Description:
 * Author: Qim Lee
 * Date: 25 Apr 2017
 */

 // This #include statement was automatically added by the Particle IDE.
 #include <neopixel.h>

 #include "Particle.h"

 SYSTEM_MODE(AUTOMATIC);

 // IMPORTANT: Set pixel COUNT, PIN and TYPE
 #define PIXEL_PIN D2
 #define PIXEL_COUNT 5
 #define PIXEL_TYPE WS2812B

 Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
 uint8_t colors[3];

 void setup() {
   Particle.function("led",ledToggle);
   Particle.function("setColor", setColor);
   Particle.function("setLedColor", setIndexColor);

   strip.begin();
   strip.show(); // Initialize all pixels to 'off'

 }

 void loop() {

 }

 void getRGBArrayFromString(String rgb) {
   int index_start = 0;
   int index_end = 0;
   int i = 0;
   while( index_end >= 0) {
       index_end = rgb.indexOf(" ", index_start);
       colors[i] = rgb.substring(index_start, index_end).toInt();
       index_start = index_end + 1;
       i = i + 1;
   }
 }

 int setColor(String input) {
   getRGBArrayFromString(input);

   uint16_t j;
   for(j=0; j<strip.numPixels(); j++) {
     strip.setPixelColor(j, colors[0], colors[1], colors[2]);
   }
   strip.show();

   return colors[0];
 }

 int ledToggle(String command) {
   if (command=="on") {
       strip.show();
       return 1;
     }
     else if (command=="off") {
       strip.clear();
       strip.show();
       return 0;
     }
     else {
       return -1;
     }
 }

 int setIndexColor(String parameter) {
   int splitIndex = parameter.indexOf(" ");
   uint16_t ledIndex = parameter.substring(0, splitIndex).toInt();
   getRGBArrayFromString(parameter.substring(splitIndex + 1));
   strip.setPixelColor(ledIndex, colors[0], colors[1], colors[2]);
   strip.show();
   return 0;
 }
