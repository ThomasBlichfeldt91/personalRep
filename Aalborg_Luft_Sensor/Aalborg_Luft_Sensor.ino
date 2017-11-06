
/*
This code intergrates an OPC-N2 air particle sensor, an SparkFun openlog data logger, 
and a LoRa radio into an Arduino Pro Mini (ATmega328P, 3.3 v, MHz). The Pro Mini will...
 */

// -----------------------------------------------------------------
// Include needed libaries. 
// -----------------------------------------------------------------

#include "opcn2.h"       
//#include <LoRa.h>
#include<SoftwareSerial.h>

// -----------------------------------------------------------------
// Initialise needed objects. 
// -----------------------------------------------------------------

OPCN2 alpha;
HistogramData hist;
SoftwareSerial logger(4,3);

// -----------------------------------------------------------------
// Define pins and sampleRate. SampleRate(ms) can be changed depending on need.
// -----------------------------------------------------------------

#define resetPin 8
#define particle_CS 9
#define lora_CS 10
#define sampleRate 5000

int counter = 0;    

// -----------------------------------------------------------------
// Setup before run. If the OPC-N2 sensor does not respond, the Pro Mini will reset. 
// -----------------------------------------------------------------   

void setup(){
    
    Serial.begin(9600);
    logger.begin(9600);
    alpha.setup(particle_CS);

    Serial.println("Testing OPC-N2 v" + String(alpha.firm_ver.major) + "." + String(alpha.firm_ver.minor));
    
    // Read and print the configuration variables
    /*LoRa.setPins(loraCsPin, resetPin, intPin);

    if (!LoRa.begin(868E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    }else{
    Serial.println("LoRa is ON!");  
    }
    */
    if(alpha.toggle_fan(true) == 0){
        pinMode(resetPin, OUTPUT);
        delay(5);
        digitalWrite(resetPin, HIGH);
        }
      
    delay(500);
    alpha.on();
    delay(500);
}

// -----------------------------------------------------------------
// The main code is now running. Depending on the sample rate, the readings will be written onto the logger.
// Readings seem to be affected by sample rate, so it is recommended to test a sample rate before using it. 
// There is a minimum natural sample rate of ~ 0.56 - 0.57 sec.  
// -----------------------------------------------------------------   

void loop(){

    hist = alpha.read_histogram();

    if ((hist.pm1 + hist.pm25 + hist.pm10) > 0 && hist.period > 0){
      // Print out the histogram data
      Serial.print("\nSampling Period:\t"); Serial.println(hist.period);
      Serial.println("");
      Serial.println("--PM values--");
      Serial.print("PM1: "); Serial.println(hist.pm1);
      Serial.print("PM2.5: "); Serial.println(hist.pm25);
      Serial.print("PM10: "); Serial.println(hist.pm10);
      Serial.println("");
      Serial.println("--bin values--");
      Serial.print("bin1: "); Serial.println(hist.bin0);
      Serial.print("bin2: "); Serial.println(hist.bin1);
      Serial.print("bin3: "); Serial.println(hist.bin2);
      Serial.print("bin4: "); Serial.println(hist.bin3);
      Serial.print("bin5: "); Serial.println(hist.bin4);
      Serial.print("bin6: "); Serial.println(hist.bin5);
      Serial.print("bin7: "); Serial.println(hist.bin6);
      Serial.print("bin8: "); Serial.println(hist.bin7);
      Serial.print("bin9: "); Serial.println(hist.bin8);
      Serial.print("bin10: "); Serial.println(hist.bin9);
      Serial.print("bin11: "); Serial.println(hist.bin10);
      Serial.print("bin12: "); Serial.println(hist.bin11);
      Serial.print("bin13: "); Serial.println(hist.bin12);
      Serial.print("bin14: "); Serial.println(hist.bin13);
      Serial.print("bin15: "); Serial.println(hist.bin14);
      Serial.print("bin16: "); Serial.println(hist.bin15);
      Serial.println("");

      logger.print("\nSampling Period:\t"); logger.println(hist.period);
      logger.println("");
      logger.println("--PM values--");
      logger.print("PM1: "); logger.println(hist.pm1);
      logger.print("PM2.5: "); logger.println(hist.pm25);
      logger.print("PM10: "); logger.println(hist.pm10);
      logger.println("");
      logger.println("--bin values--");
      logger.print("bin1: "); logger.println(hist.bin0);
      logger.print("bin2: "); logger.println(hist.bin1);
      logger.print("bin3: "); logger.println(hist.bin2);
      logger.print("bin4: "); logger.println(hist.bin3);
      logger.print("bin5: "); logger.println(hist.bin4);
      logger.print("bin6: "); logger.println(hist.bin5);
      logger.print("bin7: "); logger.println(hist.bin6);
      logger.print("bin8: "); logger.println(hist.bin7);
      logger.print("bin9: "); logger.println(hist.bin8);
      logger.print("bin10: "); logger.println(hist.bin9);
      logger.print("bin11: "); logger.println(hist.bin10);
      logger.print("bin12: "); logger.println(hist.bin11);
      logger.print("bin13: "); logger.println(hist.bin12);
      logger.print("bin14: "); logger.println(hist.bin13);
      logger.print("bin15: "); logger.println(hist.bin14);
      logger.print("bin16: "); logger.println(hist.bin15);
      logger.println("");
    } 
    delay(sampleRate);  
}

