import pygame
import math

# Inicializar Pygame
pygame.init()

# Definir el tamaño de la ventana
screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))

# Definir colores
black = (0, 0, 0)
white = (255, 255, 255)

# Definir variables para guardar las coordenadas de los segmentos
points = []
angles = []
def transform_angle(ang):
    if ang > 90:
        ang = 180 - ang
    elif ang < -90:
        ang = -180 - ang
    return ang + 90
# Bucle principal del juego
running = True
while running:
    # Gestionar eventos
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
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
                    angles.append(transform_angle(ang_grados))

        elif event.type == pygame.MOUSEBUTTONUP:
            # Si el usuario suelta el botón del ratón, guardar la posición del ratón como el final de un segmento
            pass

    # Dibujar los segmentos
    screen.fill(white)
    for i in range(len(points) - 1):
        pygame.draw.line(screen, black, points[i], points[i+1], 2)

    # Dibujar todos los ángulos calculados
    font = pygame.font.Font(None, 36)
    for i in range(len(angles)):
        text = font.render(str(round(angles[i], 2)), True, black)
        text_rect = text.get_rect(center=((points[i][0] + points[i+1][0])//2, (points[i][1] + points[i+1][1])//2))
        screen.blit(text, text_rect)

    # Actualizar la pantalla
    pygame.display.flip()

# Cerrar Pygame al salir del programa
pygame.quit()


