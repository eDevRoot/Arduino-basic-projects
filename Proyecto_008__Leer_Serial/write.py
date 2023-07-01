import serial, time, sys

if (len(sys.argv) > 1):
	arduino = serial.Serial('/dev/cu.usbmodem14201', 9600)
	time.sleep(2)
	cadena = ""
	sq = sys.argv[1:]
	for str in sq:
		if cadena != "":
			cadena = cadena + " " + str
		else:
			cadena = str
	arduino.write(cadena)
	arduino.close()
else:
	print "Debes indicar una frase"
