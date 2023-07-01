Material Necesario:
	+ Arduino
	+ Display
	+ DHT11
	+ Fuente de alimentación externa
	+ Pulsador
	+ Resistncia de 1 KOhm
	
	+ (Lector de SD's)

Descripticon:
	Usando la alimentación externa, quiero que el arduino vaya haciendo lecturas del sensor de
	temperatura y humedad cada 5 minutos y las vaya guardado en una tarjeta SD.
	La escritura será en un fichero de texto plano con el formato siguiente:

	FECHA;HORA;TEMP;HUM;

	Con este formato, luego se podra llevar facilmente a un excel o base de datos.

	Además el sistema tendrá un pulsador que encenderá el display y mostrará la última lectura durante 5 segundos.