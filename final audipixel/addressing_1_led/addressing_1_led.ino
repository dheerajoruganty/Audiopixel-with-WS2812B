// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

int sensorPin=A1;
void setup()
{
  pinMode(sensorPin, INPUT);
  Serial.begin (9600);
  unsigned long previousMillis = 0;
  
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
}





void loop() {
  // put your main code here, to run repeatedly:
int val;
int db,dbclr,dbprev;
int trigger;
int correctionFactor;
//const corfac;

correctionFactor=56;
//corfac=56;
unsigned long currentMillis = millis();
 val =analogRead(sensorPin);//it varies every time so gotta update the value after initialising the sensor
 
 db = (val+83.2073) / 11.003; //Convert ADC value to dB using Regression values
 
 //delay(20);
 if(db<correctionFactor) //mean = 513
 {
   db=(db-correctionFactor)*(-1);
   //db=db+correctionFactor;
 }
 else 
 {
   db=db-correctionFactor;
 }
 
  //Serial.println (db);

 
 if (db>=4)
 {
  //Serial.println ("1");
  trigger=1;
  for(int n=0;n<strip.numPixels();n++)
  {
  strip.setPixelColor(0,255,0,0);
  strip.show();
  }
  //Serial.println (trigger);
 }
 else
 {
  //Serial.println ("0");
  Serial.println (db);
  for(int n=0;n<strip.numPixels();n++)
  {
  strip.setPixelColor(n,0,0,255);
  strip.show();
  }
  //Serial.println (trigger);
 }
    



 

}
