#include <SPI.h>
#include <RH_RF95.h>
#include <Adafruit_DotStar.h>
#include <ArduinoJson.h>

//#define NUMPIXELS  192 // Number of LEDs in strip

//#define VBATPIN A7

   // Here's how to control the LEDs from any two pins:
#define DATAPIN    12
#define CLOCKPIN   13
Adafruit_DotStar strip = Adafruit_DotStar(192, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

#define BRIGHTNESS A0

// Blinky on receipt
#define LED 13

/*
 * Radio Driver specs for feather m0
 */
#define RFM95_CS 8 
#define RFM95_RST 4 
#define RFM95_INT 3

// Change to 434.0 or other frequency, must match RX's freq! 
#define RF95_FREQ 433.0

// Singleton instance of the radio driver 
//RH_RF95 rf95(8, 3); // Adafruit Feather M0 with RFM95 
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// radio specific info
int16_t packetnum = 0; // packet counter, we increment per xmission



void setup() {
  // put your setup code here, to run once:

  //radio setup
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(9600);
  //while (!Serial) ; // Wait for serial port to be available
  
  delay(100);
  Serial.println("Feather LoRa TX Test!");
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); 
  Serial.println(RF95_FREQ);
  
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);

  /*
   *  blank out the LED strip
   */
  clearStrip();
  //delay(200);
}
