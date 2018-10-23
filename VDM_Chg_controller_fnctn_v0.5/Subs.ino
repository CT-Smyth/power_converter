void chargeControl() {

  //Serial.println("executing charge control");

  switch (chgMode){

    case 1:
      //Serial.println("executing mode 1");
      Vtrig = 25.2;
      Vtarg = 26.5;
      VfloatMin = 26;
      VfloatMax = 26.5;
      charge();
    break;
    
    case 2:
      //Serial.println("executing mode 2");
      Vtrig = 24;
      Vtarg = 28;
      VfloatMin = 27;
      VfloatMax = 27.5;
      charge();
    break;
  
    case 3:
     //Serial.println("executing mode 3");
      Vtrig = 27.5;
      Vtarg = 28.5;
      VfloatMin = 28;
      VfloatMax = 28.5;
      charge();
    break;
  
    default:
    //Serial.println("executing mode 0");
      Shutdown();
  }

  chgTimeDue = timeNow + chg_delay;
}


void charge(){
  
  int RawValue = 0;
  double tempVoltage = 0;
  double Amps = 0;

  RawValue = get_value(voltagePin);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Voltage = Voltage /100; //voltage divider correction

  if (Voltage > Vmax) {
    Shutdown();
    Serial.println("!!!!!!!!!!!!!!!!Max voltage shutdown!!!!!!!!!!!!!!!");
    return;
  }

  if (Voltage < Vmin) {
    Shutdown();
    Serial.println("!!!!!!!!!!!!!!!!Low voltage shutdown!!!!!!!!!!!!!!!");
    return;
  }

  if (Voltage < Vtrig) bulkMode = true;
  if (Voltage > Vtarg) bulkMode = false;
  

  for (int t = 1; t < 5; t++){
      
      int cur = get_current(t);

      //Serial.print("current is .............");
      //Serial.println(cur);
      
      if (cur > 20){
        Shutdown();
        Serial.println("!!!!!!!!!!!!!!!!Max current shutdown!!!!!!!!!!!!!!!");
        return;
      }
  
      if (cur > maxCurrent + 2){
        pot_to_1k(t);
      }

      if (cur > maxCurrent){
        pot_up(t);
      }
  
      if (bulkMode == true){
        if (cur > (targetCurrent + 1)) pot_up(t);
        if (cur < (targetCurrent - 1)) pot_down(t);
      } else {
        double floatCurTarget = ((VfloatMax - Voltage) / (VfloatMax-VfloatMin)) * targetCurrent;
        if (floatCurTarget > targetCurrent) floatCurTarget = targetCurrent; //avoids above 1 multiplier of target current
        if (floatCurTarget < 1) pot_to_1k(t); //avoids irrational target currents
        if (cur > (floatCurTarget + 1)) pot_up(t);
        if (cur < (floatCurTarget - 1)) pot_down(t);
      }
   }
}





void Shutdown(){

      Serial.println("Full system shutdown");
  
      pot_to_1k(1);
      pot_to_1k(2);
      pot_to_1k(3);
      pot_to_1k(4);
}




void get_RPM(){
  
    pulseTotal = 0;
    
    for (int t=0;t<2;t++) {   //number of times for sampling
      pulseHigh = pulseIn(freqPin,HIGH);
      pulseLow = pulseIn(freqPin,LOW);
      pulseTotal = pulseTotal + pulseHigh + pulseLow; // Time period of the pulse in microseconds

    }

    pulseTotal = pulseTotal / 2;
    
    frequency=1000000/pulseTotal; // Frequency in Hertz (Hz)

    RPMTimeDue = timeNow + RPM_delay;
    
    Serial.print("Frequency : ");
    Serial.println(frequency);
}

int get_current(int channel){
  
  int RawValue = 0;
  double tempVoltage = 0;
  double Amps = 0;
  
  switch (channel) {
    case 1:
      RawValue = get_value(current1Pin);
      tempVoltage = (RawValue / 1024.0) * 5000; // Gets you mV
      Amps = ((tempVoltage - ACSoffset) / mVperAmp);
      Amps = Amps * -1;
      return Amps;
      break;
    case 2:
      RawValue = get_value(current2Pin);
      tempVoltage = (RawValue / 1024.0) * 5000; // Gets you mV
      Amps = ((tempVoltage - ACSoffset) / mVperAmp);
      Amps = Amps * -1;
      return Amps;
      break;
    case 3:
      RawValue = get_value(current3Pin);
      tempVoltage = (RawValue / 1024.0) * 5000; // Gets you mV
      Amps = ((tempVoltage - ACSoffset) / mVperAmp);
      Amps = Amps * -1;
      return Amps;
      break;
    case 4:
      RawValue = get_value(current4Pin);
      tempVoltage = (RawValue / 1024.0) * 5000; // Gets you mV
      Amps = ((tempVoltage - ACSoffset) / mVperAmp);
      Amps = Amps * -1;
      return Amps;
      break;
    default:
      Serial.println("Analog pin Selection Error");
  }
}


int get_value(int pin){
  int analogvalue = 0;

  for (int t=1;t<31;t++){
    analogvalue = analogvalue + analogRead(pin);
    delay(1);                                     //ensure that  about 1/30th of a second is measured in this loop
  }

  return (analogvalue / 30);
  
}

void report(){
  dispTimeDue = timeNow + disp_delay;

  int RawValue = 0;
  double tempVoltage = 0;
  double Amps = 0;

  // Serial.print("freq pin = ");
  // Serial.println(digitalRead(freqPin));
  
 
  Serial.print(" Amps = ");
  for (int t=1; t<5; t++){
    Serial.print(get_current(t));
    Serial.print("...");
  }
   
  RawValue = get_value(voltagePin);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Voltage = Voltage /100; //voltage divider correction
   
  Serial.print("Volts = ");
  Serial.println(Voltage); 

  Serial.print("Charge Mode .............");
  Serial.println(chgMode);
}



void one_sec(){
  dispTimeDue = timeNow + disp_delay;
  // get_RPM(); // check frequency
  report();
}



