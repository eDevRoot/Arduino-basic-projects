#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

boolean first;

void setup(){                

  first = true;
  
  Serial.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  
}


void loop() {

   if (Serial.available()>0) 
   {
    showMessage(Serial.readString());
   }else{
    if (first){
      blinkCursor();
    }
   }
  
}

void blinkCursor(){
    display.drawRoundRect(0, 0, 20, 20, 5, WHITE);
    //display.fillCircle(10, 10, 10, WHITE); 
    display.display();
    delay(500);
    display.clearDisplay();
    display.display();
    delay(500);
}

void showMessage(String message){
  first = false;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(message);
  display.display();
}

