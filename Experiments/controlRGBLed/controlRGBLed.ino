const int pinR = 14;
const int pinG = 15;
const int pinB = 16;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void loop() 
{
  int value = 0;
  analogWrite(pinR, value);
  analogWrite(pinG, value);
  analogWrite(pinB, value);
 
  for (int i=0;i<255;i++){
    analogWrite(pinR, i);
    delay(10);
  }
  for (int i=0;i<255;i++){
    analogWrite(pinG, i);
    delay(10);
  }
  for (int i=0;i<255;i++){
    analogWrite(pinB, i);
    delay(10);
  }
  delay(1000);
  
}
