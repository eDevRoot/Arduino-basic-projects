#include <SD.h>

File myFile;
void setup()
{
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
}

void loop()
{
  myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo
  
  if (myFile) { 
        Serial.print("Escribiendo SD: ");
        myFile.print("Tiempo(ms)=");
        myFile.print(millis());
        myFile.print(", sensor1=");
        myFile.print(10);
        myFile.print(", sensor2=");
        myFile.print(20);
        myFile.print(", sensor3=");
        myFile.println(30);
        
        myFile.close(); //cerramos el archivo
        
        Serial.print("Tiempo(ms)=");
        Serial.print(millis());
        Serial.print(", sensor1=");
        Serial.print(10);
        Serial.print(", sensor2=");
        Serial.print(20);
        Serial.print(", sensor3=");
        Serial.println(30);       
                    
  
  } else {
    Serial.println("Error al abrir el archivo");
  }
  delay(100);
}
