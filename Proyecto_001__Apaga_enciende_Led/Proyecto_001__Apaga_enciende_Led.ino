#define ledPin 13
#define INTERVAL 1000

void setup() {
  // put your setup code here, to run once:
  pinMode (ledPin, OUTPUT);
  
}

void loop() {
  digitalWrite(ledPin , HIGH);  // Enciende el LED
  delay(INTERVAL);              // Esperar un segundo
  digitalWrite(ledPin , LOW);   // Apagar el LED
  delay(INTERVAL);              // Esperar otro segundo
 }
