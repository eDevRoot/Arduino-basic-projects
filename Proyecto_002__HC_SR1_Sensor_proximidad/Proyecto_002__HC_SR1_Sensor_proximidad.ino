#define trigPin 13
#define echoPin 12
#define led 2

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  long duracion, distancia ;

  digitalWrite(trigPin, LOW);        // Nos aseguramos de que el trigger está desactivado
  delayMicroseconds(2);              // Para asegurarnos de que el trigger esta LOW

  digitalWrite(trigPin, HIGH);       // Activamos el pulso de salida
  delayMicroseconds(100);            // Esperamos 10µs. El pulso sigue active este tiempo
  digitalWrite(trigPin, LOW);        // Cortamos el pulso y a esperar el echo


  duracion = pulseIn(echoPin, HIGH) ;
  distancia = duracion / 2 / 29.1  ;
  Serial.println(String(distancia) + " cm.") ;

  int Limite = 50 ;                  // Medida en vacío del sensor
  if ( distancia < Limite)
        digitalWrite (led , HIGH) ;
  else
        digitalWrite( led , LOW) ;
  delay (500) ;                  // Para limitar el número de mediciones
}
