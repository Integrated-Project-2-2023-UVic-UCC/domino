import serial
import time

# Configuración del puerto serial
bluetooth_port = '/dev/tty.HC-06'  # Reemplaza por la dirección MAC de tu módulo Bluetooth
bluetooth_baud = 9600  # Velocidad de transmisión del puerto serial

# Crea el objeto serial y espera a que se establezca la conexión
ser = serial.Serial(bluetooth_port, bluetooth_baud)
time.sleep(2)  # Espera 2 segundos para que se establezca la conexión

# Lista de puntos a enviar
puntos = [ (1,2), (3,4), (5,6) ]  # Ejemplo

# Envía los datos
for punto in puntos:
    x, y = punto
    ser.write(f'{x},{y}\n'.encode())  # Envía los datos como una cadena de texto con formato x,y

# Cierra la conexión
ser.close()
