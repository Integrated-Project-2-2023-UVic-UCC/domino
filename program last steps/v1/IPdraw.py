import math
import serial
import pygame 
from shapely.geometry import LineString 
import struct
import time

# Function to calculate the distance between 2 points
def calc_dist(x1, y1, x2, y2):
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)



def transform_angle(ang):
    if ang > 90:
        ang = 180 - ang
    elif ang < -90:
        ang = -180 - ang
    return ang + 90


# Inicializar pygame 
pygame.init() 
 
# Definir las dimensiones de la pantalla 
width, height = 800, 600 
screen = pygame.display.set_mode((width, height)) 
pygame.display.set_caption("Dibuja una línea") 
 
# Definir los colores 
BLACK = (0, 0, 0) 
WHITE = (255, 255, 255) 
 
# Definir una lista para almacenar los puntos de la línea 
points = [] 
angles = []
# Definir una variable para indicar si el usuario está dibujando 
drawing = False 
 
# Bucle principal del programa
exit_flag = False
while not exit_flag: 
    # Capturar eventos 
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit_flag = True
        elif event.type == pygame.MOUSEBUTTONDOWN:
            # Si el usuario hace clic, guardar la posición del ratón como el final de un segmento
            mouse_pos = pygame.mouse.get_pos()
            points.append(mouse_pos)
            if len(points) > 1:
                # Calcular el ángulo entre los dos últimos segmentos y guardar el resultado
                if len(points) > 2:
                    vec1 = (points[-2][0] - points[-3][0], points[-2][1] - points[-3][1])
                    vec2 = (points[-1][0] - points[-2][0], points[-1][1] - points[-2][1])
                    ang = math.atan2(vec2[1], vec2[0]) - math.atan2(vec1[1], vec1[0])
                    ang_grados = math.degrees(ang)
                    if ang_grados < -180:
                        ang_grados += 360
                    elif ang_grados > 180:
                        ang_grados -= 360
                    angles.append(int(transform_angle(ang_grados)))

        elif event.type == pygame.MOUSEBUTTONUP:
            # Si el usuario suelta el botón del ratón, guardar la posición del ratón como el final de un segmento
            pass
 
    # Dibujar en la pantalla 
    screen.fill(WHITE) 
    if drawing: 
        if len(points) >= 2: 
            pygame.draw.lines(screen, BLACK, False, points, 2) 
 
    # Actualizar la pantalla 
        pygame.display.update() 
 
    else: 
        # Dibujar la línea completa cuando el usuario deja de dibujar 
        if len(points) > 1: 
            pygame.draw.lines(screen, BLACK, False, points, 2) 
 
    # Actualizar la pantalla 
    pygame.display.update() 

pygame.quit()
    

    

#calculations 




x = [i[0] for i in points]
y = [i[1] for i in points]






distancias = []

for i in range(0,len(x)-1):
        w = calc_dist(x[i-1],y[i-1],x[i],y[i])
        distancias.append(int(w))
        
           
    
angles.insert(0, 90)    
print(points)
print(angles) 
print(distancias) 

# passing the data

angles_bytes = struct.pack('i'*len(angles), *angles)

ser = serial.Serial('COM3', 9600)  #change the com3 to the bluetooth serial port
ser.write(angles_bytes)
ser.flush()
time.sleep(1)
print()
print('terminal mode:')

for i in range(len(distancias)):
    dadoangle = angles[i]
    dadodistance = distancias[i]
    ser.write(dadoangle.encode())
    time.sleep(0.2)
    ser.write(dadodistance.encode())
    time.sleep(1)
    b = ser.readline()
    if b:
        print(b)
        ser.flush
        
        
    else:
        break
    
    



