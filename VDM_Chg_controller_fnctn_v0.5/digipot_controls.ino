
void pot_down(int potNumber){
  digitalWrite(INC,HIGH); //set up the increment line to increment on low transition & wiper safety
  delayMicroseconds(100);
  digitalWrite(UD,HIGH); //High for up, low for down
  delayMicroseconds(100);
  CS_low (potNumber);
  digitalWrite(INC,LOW); //move wiper as per UD bit
  delayMicroseconds(100);
  CS_high (potNumber);
}

void pot_up(int potNumber){
  digitalWrite(INC,HIGH); //set up the increment line to increment on low transition & wiper safety
  delayMicroseconds(100);
  digitalWrite(UD,LOW); //High for up, low for down
  delayMicroseconds(100);
  CS_low (potNumber);
  digitalWrite(INC,LOW); //move wiper as per UD bit
  delayMicroseconds(100);
  CS_high (potNumber);
}

void pot_store(int potNumber){
  delay(1);
  digitalWrite(INC,HIGH); //set up the increment line to increment on low transition & wiper safety
  delay(1);
  CS_low (potNumber); // Select Chip
  delay(1);
  CS_high (potNumber); //Deselect Chip (stores value because INC is high)
  delay(1);
}


void pot_1k_setval(int potNumber, int val){
  if (val > 100) val = 100;
  if (val < 0) val = 0;
  pot_to_1k(potNumber);
  val = 100 - val;
  for (int t = 0;t<val;t++){
    pot_down(potNumber);
  }  
}

void pot_0k_setval(int potNumber, int val){
  if (val > 100) val = 100;
  if (val < 0) val = 0;
  pot_to_0k(potNumber);
  for (int t = 0;t<val;t++){
    pot_up(potNumber);
  }  
}



void pot_to_1k(int potNumber){
  for (int t = 0;t<101;t++){
    pot_up(potNumber);
  }
}

void pot_to_0k(int potNumber){
  for (int t = 0;t<101;t++){
    pot_down(potNumber);
  }
}

void CS_high(int potNumber){
  
    switch (potNumber) {
    case 1:
      digitalWrite(CS1,HIGH); 
      break;
    case 2:
      digitalWrite(CS2,HIGH);
      break;
    case 3:
      digitalWrite(CS3,HIGH);
      break;
    case 4:
      digitalWrite(CS4,HIGH);
      break;
    default:
      Serial.println("Select_High Selection Error");
  }

  delayMicroseconds(100);
}



void CS_low(int potNumber){
  
    switch (potNumber) {
    case 1:
      digitalWrite(CS1,LOW);
      break;
    case 2:
      digitalWrite(CS2,LOW);
      break;
    case 3:
      digitalWrite(CS3,LOW);
      break;
    case 4:
      digitalWrite(CS4,LOW);
      break;
    default:
      Serial.println("Select_Low Selection Error");
  }

  delayMicroseconds(100);
}



