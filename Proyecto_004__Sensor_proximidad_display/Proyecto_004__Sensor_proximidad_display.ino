#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCD.h>


#define I2C_ADDR    0x27
#define trigPin 13
#define echoPin 12

LiquidCrystal_I2C             lcd(I2C_ADDR,2, 1, 0, 4, 5, 6, 7);

void setup()
{
  // Inicializar el display con 16 caraceres 2 lineas
  lcd.begin (20,4);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() 
{
  long duracion, distancia ;
  
  digitalWrite(trigPin, LOW);        // Nos aseguramos de que el trigger está desactivado
  delayMicroseconds(2);              // Para asegurarnos de que el trigger esta LOW
  
  digitalWrite(trigPin, HIGH);       // Activamos el pulso de salida
  delayMicroseconds(100);            // Esperamos 10µs. El pulso sigue active este tiempo
  digitalWrite(trigPin, LOW);        // Cortamos el pulso y a esperar el echo
  
  duracion = pulseIn(echoPin, HIGH) ;
  distancia = duracion / 2 / 29.1 ;
  
  int Limite = 50 ;                  // Medida en vacío del sensor
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distancia: " + String(distancia) + " cm");
  delay (500) ;                      // Para limitar el número de mediciones
}

void writeString(String text, int row)
{
  lcd.setCursor(0,row);
  lcd.print(text);
}
