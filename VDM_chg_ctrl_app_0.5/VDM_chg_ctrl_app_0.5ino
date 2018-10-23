//for ESP8266

#include <Encoder.h>
#include <Wire.h>
//#include "SSD1306Wire.h"
#include "SH1106Wire.h"

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])



const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = D2; 
const int SDC_PIN = D1;
const int SW_PIN = D7;
const int DT_PIN = D6;
const int CLK_PIN = D5;

String modes[] {"0","...","Off","Carga Maint", "Normal","Carga Max","...","6"};

long oldPosition  = -999;

int chgMode = 1;
int menu = -1;

unsigned long timeNow = millis();
const unsigned long disp_delay = 1000;
unsigned long dispTimeDue = timeNow + disp_delay;

// Create display
//SSD1306Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);
SH1106Wire     display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);


// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(CLK_PIN, DT_PIN);
//   avoid using pins with LEDs attached



void setup() {
  Serial.begin(57600);

  pinMode(SW_PIN, INPUT_PULLUP);

//  for (int t=0; t < ARRAY_SIZE(modes);t++){
//    String output = "mode ";
//    output+= String(t);
//    output+= "...";
//    output+= modes[t];
//    Serial.println(output);
//  }

// initialize display
  display.init();
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setContrast(128);



//myEnc.write(0);

}



void loop() {
  
  timeNow = millis();
  
  long newPosition = myEnc.read();

  
  if (newPosition != oldPosition) {
    
    if ((newPosition - oldPosition) > 3) {
      menu++;
      myEnc.write(0);
      oldPosition = 0;
      newPosition = 0;

      if (menu < 1) menu = 0;
      if (menu > (ARRAY_SIZE(modes)-5)) menu = ARRAY_SIZE(modes)-5;

      disp_menu_move(menu);
    }

    
    if ((oldPosition - newPosition) > 3) {
      menu--;
      myEnc.write(0);
      oldPosition = 0;
      newPosition = 0;
      
      if (menu < 1) menu = 0;
      if (menu > (ARRAY_SIZE(modes)-5)) menu = ARRAY_SIZE(modes)-5;

      disp_menu_move(menu);
    }

    if (menu < 1) menu = 0;

    if (menu > (ARRAY_SIZE(modes)-5)) menu = ARRAY_SIZE(modes)-5;

    disp_menu_move(menu);

  }

  if (timeNow > dispTimeDue) disp_menu(menu);

  if (digitalRead(SW_PIN) == 0) {
    menu = 0;
    disp_menu(menu);
  }

}
