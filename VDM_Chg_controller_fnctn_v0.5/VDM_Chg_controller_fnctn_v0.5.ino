//for Arduino Nano or ATMega328PA or equivelant
 
//#include <FreqCount.h>

#define INC 12   // D1 Mini D4 - pulled up in H/W (10k) ->  chip pin 1
#define UD 11  // D1 Mini D8                          ->  chip pin 2
#define CS1 10   // D1 Mini D0 - pulled up in H/W (10k) ->  2nd chip pin 7
#define CS2 9
#define CS3 8
#define CS4 7
#define freqPin 5
#define current1Pin A0
#define current2Pin A1
#define current3Pin A2
#define current4Pin A3
#define voltagePin A4


// "up" and "down" make sense in relation to the wiper pin 5 [VW/RW] and the HIGH end of the pot
// i.e. pin 3 [VH/RH], leaving pin 6 [VL/RL] unused (floating). You can easily use pin 6 instead
// pin 3, but "min" will actually mean "max" and vice versa. Also, the "setPot" percentage will
// set the equivalent of 100-<value>, i.e. setPot(70) will set the resistance between pins 5 and 6 
// to 30% of the maximum. (Of course in that case,the "unused" resistance between 5 and 3 will be 70%)
// Nothing to stop you using it as a full centre-tap potentiometer, the above example giving
// pin 3[H] -- 70% -- pin 5[W] -- 30% -- pin 6[L]



bool  bulkMode = true;


int pulseHigh; // Integer variable to capture High time of the incoming pulse
int pulseLow; // Integer variable to capture Low time of the incoming pulse


const int mVperAmp = 66; // use 185 for 5A Module, 100 for 20A Module and 66 for 30A Module
const int ACSoffset = 2500; //2500


int chgMode = 0;



float pulseTotal; // Float variable to capture Total time of the incoming pulse
float frequency; // Calculated Frequency

double Vtrig = 24;
double Vtarg = 27;
double VfloatMin = 26;
double VfloatMax = 26.5;
const double Vmax = 29.5;
const double Vmin = 18;

const double maxCurrent = 15;
const double targetCurrent = 12;



double Voltage = 0;


long num = 0;

unsigned long timeNow = millis();
const unsigned long disp_delay = 1000;
const unsigned long RPM_delay = 400; //2.5 times a second
const unsigned long chg_delay = 255; //4 times a second
unsigned long RPMTimeDue = timeNow + RPM_delay;
unsigned long dispTimeDue = timeNow + disp_delay;
unsigned long chgTimeDue = timeNow + chg_delay;


int incomingByte;      // a variable to read incoming serial data into



void setup(){
pinMode(freqPin,INPUT);

pinMode(INC,OUTPUT);
pinMode(UD,OUTPUT);
pinMode(CS1,OUTPUT);
pinMode(CS2,OUTPUT);
pinMode(CS3,OUTPUT);
pinMode(CS4,OUTPUT);

digitalWrite(UD,HIGH);
digitalWrite(INC,LOW);
digitalWrite(CS1,HIGH);
digitalWrite(CS2,HIGH);
digitalWrite(CS3,HIGH);
digitalWrite(CS4,HIGH);

digitalWrite (freqPin,true); //pullup
//FreqCount.begin(1000);
Serial.begin(57600); 
Serial.println("Energy converter function program");

pinMode(3,OUTPUT); //signal generator for testing
analogWrite(3,75); //signal generator for testing

//analogWrite (12,100);
//analogWrite (11,150);
//analogWrite(10,200);


//pot_1k_setval(1,20); //set these to test POT writing functions
//pot_1k_setval(2,40); //set these to test POT writing functions
//pot_1k_setval(3,60); //set these to test POT writing functions
//pot_1k_setval(4,80); //set these to test POT writing functions


}





void loop() { 

timeNow = millis(); 
  
  
if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();

    if (incomingByte == '0') chgMode = 0;

    if (incomingByte == '1') chgMode = 1;

    if (incomingByte == '2') chgMode = 2;

    if (incomingByte == '3') chgMode = 3;

    
    
//  Serial.print("Operation Mode = ");
//  Serial.println(chgMode);  
}





if (timeNow > chgTimeDue) chargeControl();
if (timeNow > dispTimeDue) one_sec();
// if (timeNow > RPMTimeDue) get_RPM();
 
}
