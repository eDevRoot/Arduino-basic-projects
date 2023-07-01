#include <LCD.h>
#include <SD.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN 3
#define DHTTYPE DHT11       // DHT 11 

DHT dht(DHTPIN, DHTTYPE);                                         //Indica el pin con el que trabajamos y el tipo de sensor
LiquidCrystal_I2C lcd(0x27,2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);     //Indica la dirección de memoria IC2 del display
  
bool LCDState = true;
bool doSomething = false;

long interval = 300000; // 5 min.
long counter = 0;
float time = 0;
File file;
int h;
int t;

void setup() {
  
  //Inicializa el puerto Serie
  Serial.begin(9600);
  
  //Inicializa el display con 16 caraceres 2 lineas
  lcd.begin (20,4);
  lcd.setBacklight(LOW);

  //Inicializa el Sensor DHT
  dht.begin();

  //Inicializa el Modulo SD
  SD.begin(4);
  
  //Creamos las interrupciones
  attachInterrupt( 0, ServicioBoton, FALLING);
}
   
void loop() {

  //Si tenemos un trabajo activo
  if (doSomething) {
    //Si activamos el botón (interrupción)
    if (LCDState){
      
      //Encendemos pantalla
      lcd.setBacklight(HIGH);
      lcd.home();
      h = dht.readHumidity();
      t = dht.readTemperature();
      printInfo(h, t);
    
    }else{
      
      //Limpiamos pantalla y apagamos
      lcd.setBacklight(LOW);
      lcd.clear();
    }
    
    doSomething = false; 
  }

  //Cada Intervalo se hará una escritura en la SD correspondiente a la humedad y temperatura leídas
  if ((millis() - time) > interval) {
    h = dht.readHumidity();
    t = dht.readTemperature();
    file = SD.open("datalog.txt", FILE_WRITE);
    file.print(counter);
    file.print(";");
    file.print(h);
    file.print(";");
    file.println(t);
    file.close();
    counter++;
    time = millis();
  }
}

void printInfo(int h, int t) {
  lcd.setCursor(0,0);
  lcd.print("Humedad relativa:");
  lcd.setCursor(0,1);
  lcd.print(String(h));
  lcd.setCursor(0,2);
  lcd.print("Temperatura:");
  lcd.setCursor(0,3);
  lcd.print(String(t));
}

//Esta interrupción cambia el estado del display.
void ServicioBoton() {
  LCDState = not LCDState;
  doSomething = true;
}
