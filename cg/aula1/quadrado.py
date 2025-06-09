import sys
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

# Variáveis globais para a animação
position_x = 0.0
direction = 0.005

def display():
    glClear(GL_COLOR_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    # Aplica a translação horizontal
    glPushMatrix()
    glTranslatef(position_x, 0.0, 0.0)
    # Desenha um quadrado centrado na origem com tamanho 0.2 x 0.2,
    # atribuindo cores diferentes para cada vértice
    glBegin(GL_POLYGON)
    glColor3f(1.0, 0.0, 0.0)  # Vermelho para o vértice inferior-esquerdo
    glVertex3f(-0.1, -0.1, 0.0)
    glColor3f(0.0, 1.0, 0.0)  # Verde para o vértice inferior-direito
    glVertex3f( 0.1, -0.1, 0.0)
    glColor3f(0.0, 0.0, 1.0)  # Azul para o vértice superior-direito
    glVertex3f( 0.1,  0.1, 0.0)
    glColor3f(1.0, 1.0, 0.0)  # Amarelo para o vértice superior-esquerdo
    glVertex3f(-0.1,  0.1, 0.0)
    glEnd()
    glPopMatrix()
    
    glFlush()

def update(value):
    global position_x, direction
    # Atualiza a posição
    position_x += direction
    # Inverte a direção quando atingir os limites (usando coordenadas normalizadas)
    if position_x >= 0.5 or position_x <= -0.5:
        direction = -direction
    glutPostRedisplay()
    glutTimerFunc(16, update, 0)

def init():
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    # Define uma projeção ortográfica que abrange de -1 a 1 nos eixos x e y
    gluOrtho2D(-1, 1, -1, 1)

glutInit(sys.argv)
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
glutInitWindowSize(350, 350)
glutInitWindowPosition(100, 100)
wind = glutCreateWindow("Quadrado Animado")
init()
glutDisplayFunc(display)
glutTimerFunc(0, update, 0)
glutMainLoop()