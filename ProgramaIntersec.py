import pygame
from shapely.geometry import LineString

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
while True:
    # Capturar eventos
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()
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
            # Imprimir los puntos de la línea
            print("Punts:", points)
            # Comprobar si la línea se cruza consigo misma
            line = LineString(points)
            if line.is_simple:
                print("La línea no se cruza consigo misma")
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

