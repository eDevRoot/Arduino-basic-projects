#include "ESP8266.h"
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int BAUD_RATE = 9600;
const int INTERRUP_PIN = 2;
const char* SSID = "C3P0";
const char* SSID_PASSWORD = "Sandra_Antonio_Ludo@2020";

volatile byte mode = 0;
byte prevMode = 9;

SoftwareSerial softSerial(10, 11); // RX, TX
ESP8266 wifi(softSerial);
LiquidCrystal_I2C lcd(0x27,20,4);  // Dirección de la pantalla, columnas, filas

void setup() {
  Serial.begin(BAUD_RATE);
  softSerial.begin(BAUD_RATE);

  setupLCD();
  lcd.print("Booting");
  
  setupWifi();
  
  //Establecemos el Pin de entrada
  pinMode(INTERRUP_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUP_PIN), changeMode, FALLING);
}

void setupLCD() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void setupWifi() {
  Serial.println("setup begin");
  wifi.restart();
  delay(500);
 
  if (wifi.setOprToStationSoftAP()) {
    Serial.println("to station + softap ok");
  }else{
    mode = 6;  
    Serial.println("to station + softap err");
  }
 
  if (wifi.joinAP(SSID, SSID_PASSWORD)) {
    Serial.println("Join AP success");
    Serial.println("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  }else{
    mode = 6;
    Serial.println("Join AP failure");
  }
 
  if (wifi.enableMUX()) {
    Serial.println("multiple ok");
  }else{
    mode = 6;
    Serial.println("multiple err");
  }
 
  if (wifi.startTCPServer(80)) {
    Serial.println("start tcp server ok");
  }else{
    mode = 6;
    Serial.println("start tcp server err");
  }
  
  if (wifi.setTCPServerTimeout(10)) {
    Serial.println("set tcp server timout 10 seconds");
  }else{
    mode = 6;
    Serial.println("set tcp server timout err");
  }
  if (mode == 6){
    Serial.println("Setup wifi failed");
  }else{
    Serial.println("Setup wifi sucess!");
  }
   
}

// === LOOP ===
void loop() {
  createWebServer();
  printMode();
  //delay(500);
}

#define wifiWrite(A) wifi.send(mux_id, (uint8_t*) A, sizeof(A) - 1);
void createWebServer()
{
  uint8_t buffer[128] = { 0 };
  uint8_t mux_id;
  
  uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
  if (len > 0) {
    Serial.println("Received from: ");
    Serial.println(mux_id);
    Serial.println("\r\n");

    wifiWrite("HTTP/1.1 200 OK\r\nnContent-Type: /html\r\nConnection: close\r\n\r\n");
    wifiWrite("<html>\n<head>\n<title>Retro Hacker Player</title>\n</head>\n<body>");
    wifiWrite("<h2>Mode</h2>");
    wifiWrite("<button onClick=location.href='./?data=0'>0</button>");
    wifiWrite("<button onClick=location.href='./?data=1'>1</button>");
    wifiWrite("<button onClick=location.href='./?data=2'>2</button>");
    wifiWrite("<button onClick=location.href='./?data=3'>3</button>");
    wifiWrite("<button onClick=location.href='./?data=4'>4</button>");
    wifiWrite("</body></html>");
     
    for (uint32_t i = 0; i < len; i++) {
      char c = (char)buffer[i];
      if (c == '?'){
        if ((char)buffer[i + 6] == '0') mode = 0;
        else if ((char)buffer[i + 6] == '1') mode = 1;
        else if ((char)buffer[i + 6] == '2') mode = 2;
        else if ((char)buffer[i + 6] == '3') mode = 3;
        else if ((char)buffer[i + 6] == '4') mode = 4;
        break;
      }
    }
  }
}

void changeMode() {
  Serial.print("Interrup detected in pin: ");
  Serial.println(INTERRUP_PIN);

  //Si estamos en modo "sin Wifi" ignoramos la interrupción
  if (mode == 6) return;
  
  mode++;
  if (mode == 5) mode=0;
  Serial.print("New Mode selected: ");
  Serial.println(mode);
}

void printMode() {
  if (prevMode == mode) return;
  Serial.print("Current Mode: ");
  Serial.println(mode);
  switch (mode)
  {
    case 0:
    mode0();
    break;
    case 1:
    mode1();
    break;
    case 2:
    mode2();
    break;
    case 3:
    mode3();
    break;
    case 4:
    mode4();
    break;
    case 6:
    mode6();
    break;
  }
  prevMode = mode;
}

void mode0() {
  clearLCD();
  lcd.print(mode);
}

void mode1() {
  clearLCD();
  Serial.println(wifi.getVersion());
  lcd.print(wifi.getVersion());
}

void mode2() {
  clearLCD();
  Serial.println(wifi.getLocalIP());
  lcd.print(wifi.getLocalIP());
}

void mode3() {
  clearLCD();
  lcd.print(mode);
}

void mode4() {
  clearLCD();
  lcd.print(mode);
}

void mode6() {
  clearLCD();
  lcd.print("Setup WIFI Failed");
}

void clearLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
}
