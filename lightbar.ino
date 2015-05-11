int datapin = 2; 
int clockpin = 3;
int latchpin = 4;

void setup() {
  // Set the three SPI pins to be outputs:

  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
  
  digitalWrite(latchpin, LOW);
  digitalWrite(datapin, LOW);
  digitalWrite(clockpin, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  
  if(random(2)==1){
    digitalWrite(datapin, HIGH);
  }
  digitalWrite(clockpin, HIGH);
  digitalWrite(clockpin, LOW);
  digitalWrite(datapin, LOW);
  
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
  
  delay(70);
}
