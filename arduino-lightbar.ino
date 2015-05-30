int red1_datapin =   2; 
int red1_clockpin =  3;
int red1_latchpin =  4;

int grn1_datapin =   5; 
int grn1_clockpin =  6;
int grn1_latchpin =  7;

int red2_datapin =   8; 
int red2_clockpin =  9;
int red2_latchpin = 10;

int grn2_datapin =  11; 
int grn2_clockpin = 12;
int grn2_latchpin = 13;

int zone1_active = A0;
int zone1_state  = A1;
int zone2_active = A2;
int zone2_state  = A3;
int zone3_active = A4;
int zone3_state  = A5;

int redScore = 0;
int greenScore = 0;
bool gameFinished = false;

int targetScore = 64;
int scoreInterval = 1000;

unsigned long lastScoreCheck = 0;

void setup() {
  
  initOutputPin(red1_datapin);
  initOutputPin(red1_clockpin);
  initOutputPin(red1_latchpin);
  
  initOutputPin(red2_datapin);
  initOutputPin(red2_clockpin);
  initOutputPin(red2_latchpin);
  
  initOutputPin(grn1_datapin);
  initOutputPin(grn1_clockpin);
  initOutputPin(grn1_latchpin);
  
  initOutputPin(grn2_datapin);
  initOutputPin(grn2_clockpin);
  initOutputPin(grn2_latchpin);
  
  pinMode(zone1_active, INPUT);
  pinMode(zone1_state,  INPUT);
  pinMode(zone2_active, INPUT);
  pinMode(zone2_state,  INPUT);
  pinMode(zone3_active, INPUT);
  pinMode(zone3_state,  INPUT);
  
  // Purge any existing register data
  for(int i=0; i < targetScore + 1 ; i++)
  {
     writeRed(LOW);
     writeGreen(LOW); 
  }
  
  latchRed();
  latchGreen();
}

void initOutputPin(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void writeRed(int state)
{
  digitalWrite(red1_datapin, state);
  digitalWrite(red2_datapin, state);
  digitalWrite(red1_clockpin, HIGH);
  digitalWrite(red2_clockpin, HIGH);
//  delay(50);
  digitalWrite(red1_clockpin, LOW); 
  digitalWrite(red2_clockpin, LOW); 
  
  digitalWrite(red1_datapin, LOW);
  digitalWrite(red2_datapin, LOW); 
//  delay(50); 
}

void writeGreen(int state)
{
  digitalWrite(grn1_datapin, state);
  digitalWrite(grn2_datapin, state);
  digitalWrite(grn1_clockpin, HIGH);
  digitalWrite(grn2_clockpin, HIGH);
//  delay(50);
  digitalWrite(grn1_clockpin, LOW); 
  digitalWrite(grn2_clockpin, LOW);  
  
  digitalWrite(grn1_datapin, LOW);
  digitalWrite(grn2_datapin, LOW);
//  delay(50);
}

void latchRed() 
{
  digitalWrite(red1_latchpin, HIGH);
  digitalWrite(red2_latchpin, HIGH);
  digitalWrite(red1_latchpin, LOW);
  digitalWrite(red2_latchpin, LOW);
}

void latchGreen()
{
  digitalWrite(grn1_latchpin, HIGH);
  digitalWrite(grn2_latchpin, HIGH);
  digitalWrite(grn1_latchpin, LOW);
  digitalWrite(grn2_latchpin, LOW);
}


void loop() { 
  int s;
  int redPhaseScore=0;
  int greenPhaseScore=0;
  
  unsigned long timeNow = millis();
  
  
  if(gameFinished == true)
  {
   if(redScore > targetScore)
   {
     writeRed(random(0,2));
     latchRed();
   }
   else
   {
     writeGreen(random(0,2));
     latchGreen();
   }
   
   return; 
  }
  
  if ( (timeNow - scoreInterval) > lastScoreCheck) {
    
    lastScoreCheck = timeNow;
    
    // Read Score Switches
    if(digitalRead(zone1_active) == HIGH) {
      if(digitalRead(zone1_state) == HIGH) {
        redPhaseScore++;
      } else {
        greenPhaseScore++;
      }
    }
     
    if(digitalRead(zone2_active) == HIGH) {
      if(digitalRead(zone2_state) == HIGH) {
        redPhaseScore++;
      } else {
        greenPhaseScore++;
      }
    }
    
    if(digitalRead(zone3_active) == HIGH) {
      if(digitalRead(zone3_state) == HIGH) {
        redPhaseScore++;
      } else {
        greenPhaseScore++;
      }
    }
    
    if(redPhaseScore > 0)
    {
       // Update global Score
       redScore += redPhaseScore;
       
        // Write score to shift registers
        for(s = 0; s < redPhaseScore; s++) {
          writeRed(HIGH); 
        }
      
      latchRed();
    }

    if(greenPhaseScore > 0)
    {
       // Update global Score
       greenScore += greenPhaseScore;
       
        // Write score to shift registers
        for(s = 0; s < greenPhaseScore; s++) {
          writeGreen(HIGH); 
        }
      
      latchGreen();    
    }  
    
   if(redScore > targetScore)
   {
     gameFinished = true;
   }
   
   if(greenScore > targetScore)
   {
     gameFinished = true;
   }
   
    
  }

   
}
