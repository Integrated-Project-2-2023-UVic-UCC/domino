import math
import serial
import pygame 
from shapely.geometry import LineString 

# Function to calculate the distance between 2 points
def calc_dist(x1, y1, x2, y2):
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

def calc_angle(x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1
    t = math.degrees(math.atan2(dy, dx))
    if t<0:
        t = 360+t
    
    return t    

def calcular_angulo(vetor1, vetor2):
    produto_escalar = vetor1[0] * vetor2[0] + vetor1[1] * vetor2[1]
    magnitude_vetor1 = math.sqrt(vetor1[0] ** 2 + vetor1[1] ** 2)
    magnitude_vetor2 = math.sqrt(vetor2[0] ** 2 + vetor2[1] ** 2)
    cos_theta = produto_escalar / (magnitude_vetor1 * magnitude_vetor2)
    angulo_radianos = math.acos(cos_theta)
    return math.degrees(angulo_radianos)

#define the serial port 
#ser = serial.Serial('COM3', 9600)  #change the com3 to the bluetooth serial port

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
            # Empezar a dibujar 
            drawing = True 
            # Añadir el punto inicial a la lista 
            points.append(pygame.mouse.get_pos()) 
        elif event.type == pygame.MOUSEBUTTONUP: 
            # Dejar de dibujar 
            drawing = False 
            # Añadir el punto final a la lista 
            points.append(pygame.mouse.get_pos())  
            # Comprobar si la línea se cruza consigo misma 
            line = LineString(points) 
            if line.is_simple: 
                print(" ") 
            else: 
                print("La línea se cruza consigo misma") 
 
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
print(points)
origin = points[0]
'''reference_vector = (points[1][0] - origin[0], points[1][1] - origin[1])
reference_angle = math.atan2(reference_vector[1], reference_vector[0])
reference_angledegre = math.degrees(reference_angle)
if reference_angledegre < 0:
    reference_angledegre += 360
print(reference_angledegre)

for ponto in points[2:]:
    vetor_movimento = (ponto[0] - origin[0], ponto[1] - origin[1])
    angulo_movimento = math.atan2(vetor_movimento[1], vetor_movimento[0])
    angulo_movimento_graus = math.degrees(angulo_movimento)
    if angulo_movimento_graus < 0:
        angulo_movimento_graus += 360
    print (angulo_movimento_graus) '''   

for i in range(1, len(points) - 1):
    vetor1 = (points[i][0] - origin[0], points[i][1] - origin[1])
    vetor2 = (points[i+1][0] - origin[0], points[i+1][1] - origin[1])
    angulo_movimento = calcular_angulo(vetor1, vetor2)
    print("Ângulo de movimento entre o ponto", points[i], "e o ponto", points[i+1], "em graus:", angulo_movimento)








x = [i[0] for i in points]
y = [i[1] for i in points]



'''print(calc_angle(x[0],y[0],x[1],y[1]))
print(calc_angle(x[1],y[1],x[2],y[2]))
print(calc_angle(x[2],y[2],x[3],y[3]))   

angles = []
distancias = []
orientation_var = 0'''
''''for i in range(1,len(x)-1):
    if i == 1:
        angles.append(0)
        v = calc_angle(x[i-1],y[i-1],x[i],y[i])
        w = calc_dist(x[i-1],y[i-1],x[i],y[i])
        distancias.append(w)
        orientation_var = v
           
    if i>=2:
        v = calc_angle(x[i-1],y[i-1],x[i],y[i])
        w = calc_dist(x[i-1],y[i-1],x[i],y[i])
        if v>orientation_var:
            v = v-orientation_var
            angles.append(v)
        else:
            v = orientation_var-v 
            angles.append(v)  ''' 

    
'''print(orientation_var)
print('')
print(angles)'''



