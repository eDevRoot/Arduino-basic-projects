#define trigPin 13
#define echoPin 12
#define led0 0
#define led1 1
#define led2 2
#define led3 3
#define led4 4
#define LIMITE 50

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  long duracion, distancia ;
  
  digitalWrite(trigPin, LOW);        // Nos aseguramos de que el trigger está desactivado
  delayMicroseconds(2);              // Para asegurarnos de que el trigger esta LOW
  
  digitalWrite(trigPin, HIGH);       // Activamos el pulso de salida
  delayMicroseconds(100);            // Esperamos 10µs. El pulso sigue active este tiempo
  digitalWrite(trigPin, LOW);        // Cortamos el pulso y a esperar el echo
  
  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion / 2 / 29.1 ;
  Serial.println(String(distancia) + " cm.") ;
  
  if ( distancia > LIMITE) {
        digitalWrite (led0 , LOW);
        digitalWrite (led1 , LOW);
        digitalWrite (led2 , LOW);
        digitalWrite (led3 , LOW);
        digitalWrite (led4 , LOW);
  }
  
  if (distancia < 50) digitalWrite (led4 , HIGH);
  if (distancia < 40) digitalWrite (led3 , HIGH);
  if (distancia < 30) digitalWrite (led2 , HIGH);
  if (distancia < 20) digitalWrite (led1 , HIGH);
  if (distancia < 10) digitalWrite (led0 , HIGH);
  
  //Para limitar el número de mediciones
  delay (500);
}
