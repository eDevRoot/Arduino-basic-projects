#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C             lcd(0x27,2, 1, 0, 4, 5, 6, 7);
int PIN_READ = 7;
int val;
int button = 0;
String str;

void setup() 
{
  // Inicializar el display con 16 caraceres 2 lineas
  lcd.begin (20,4);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  pinMode(PIN_READ, INPUT);
}

void loop() 
{    
  button = digitalRead(PIN_READ);
  if (button == HIGH) {
    str = "HOLA";
  }else{
    str = "ADIOS";
  }
  val = analogRead(PIN_READ);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(str + String(val));
  delay(500);
}

