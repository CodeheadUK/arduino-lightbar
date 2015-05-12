int datapin = 2; 
int clockpin = 3;
int latchpin = 4;

int RedScore = 0;
int GrnScore = 0;

unsigned long lastScoreCheck = 0;

void setup() {
  
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
  
  digitalWrite(latchpin, LOW);
  digitalWrite(datapin, LOW);
  digitalWrite(clockpin, LOW);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  
}

void Write(bool state)
{
 digitalWrite(datapin, state);
 digitalWrite(clockpin, HIGH);
 digitalWrite(clockpin, LOW); 
}

void Latch() {
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}


void loop() { 
  
  int i;
  unsigned long timeNow = millis();
  
  if ( (timeNow - 1000) > lastScoreCheck) {
    
    lastScoreCheck = timeNow;
    
    // Read Score Switches
    if(digitalRead(A0) == LOW) {
      RedScore++;
     }
     
    if(digitalRead(A1) == LOW) {
     GrnScore++; 
    }
    
    if(digitalRead(A2) == LOW) {
     RedScore++;
    }
     
    if(digitalRead(A3) == LOW) {
     GrnScore++; 
    }
    
    if(digitalRead(A4) == LOW) {
     RedScore++;
    }
     
    if(digitalRead(A5) == LOW) {
     GrnScore++; 
    }
     
    // Clear registers
    for(i = 0; i < 256 ; i++) {
      Write(LOW);
    }  
    
    // Write score to shift registers
    for(i = 0; i < RedScore; i++) {
      Write(HIGH); 
    }
    
    // Latch
    Latch();
     
  }
  
  
  // Reset
  if(digitalRead(13) == LOW) {
    for(i = 0; i < 256 ; i++) {
      Write(LOW);
    }      
    Latch();
    RedScore = 0;
    GrnScore = 0;
    lastScoreCheck = millis();
    
  }
  
}
