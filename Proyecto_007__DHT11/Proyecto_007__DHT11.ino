#include "DHT.h"
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C             lcd(0x27,2, 1, 0, 4, 5, 6, 7);


#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11 

// Conecta el pin 1 (el de la izquierda) del sensor a +5V
// Conecta el pin 2 del sensor al pin que has elegido para DHTPIN
// Conecta el pin 4 (el de la derecha) del sensor a GROUND
// Conecta una resistencia de 10K del pin 2 (data) al pin 1 (+5V) del sensor
 
DHT dht(DHTPIN, DHTTYPE);  //Indica el pin con el que trabajamos y el tipo de sensor
int maxh=0, minh=100, maxt=0, mint=100;  //Variables para ir comprobando maximos y minimos
 
void setup() 
{
  // Inicializar el display con 16 caraceres 2 lineas
  lcd.begin (20,4);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  
  //Iniciamos el sensor
  dht.begin();
}
 
void loop() {
  //lcd.clear();
  lcd.setCursor(0,0);
  
  // La lectura de la temperatura o de la humedad lleva sobre 250 milisegundos  
  // La lectura del sensor tambien puede estar sobre los 2 segundos (es un sensor muy lento)
  float h = dht.readHumidity();  //Guarda la lectura de la humedad en la variable float h
  float t = dht.readTemperature();  //Guarda la lectura de la temperatura en la variable float t
 
  // Comprobamos si lo que devuelve el sensor es valido, si no son numeros algo esta fallando
  if (isnan(t) || isnan(h)) // funcion que comprueba si son numeros las variables indicadas 
  {
    lcd.print("Fallo al leer del sensor DHT"); //Mostramos mensaje de fallo si no son numeros
    
  } else {
    //Mostramos mensaje con valores actuales de humedad y temperatura, asi como maximos y minimos de cada uno de ellos
    lcd.setCursor(0,0);
    lcd.print("Humedad relativa:");
    lcd.setCursor(0,1);
    lcd.print(String(h));
    lcd.setCursor(0,2);
    lcd.print("Temperatura:");
    lcd.setCursor(0,3);
    lcd.print(String(t));
  }
  delay(1000);
}

