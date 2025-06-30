from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import pywavefront
from pywavefront import visualization
import random
import math

# Variáveis da nave (carro)
nave_x = 0.0
nave_y = 0.0
nave_z = 0.0
nave_angle = 0.0
nave_vel_x = 0.0
nave_vel_z = 0.0
nave_accel = 0.0

# Classe para asteroides
class Asteroide:
    def __init__(self, x, z, vel_x, vel_z, rot_speed):
        self.x = x
        self.z = z
        self.vel_x = vel_x
        self.vel_z = vel_z
        self.rotation = 0.0
        self.rot_speed = rot_speed
        self.size = random.uniform(0.5, 1.5)
    
    def update(self):
        self.x += self.vel_x
        self.z += self.vel_z
        self.rotation += self.rot_speed
        
        # Wrap around screen
        if self.x > 50: self.x = -50
        if self.x < -50: self.x = 50
        if self.z > 50: self.z = -50
        if self.z < -50: self.z = 50

# Lista de asteroides
asteroides = []

# Inicializar asteroides
def init_asteroides():
    global asteroides
    for i in range(8):
        x = random.uniform(-40, 40)
        z = random.uniform(-40, 40)
        # Evitar spawnar muito perto da nave
        while abs(x) < 5 and abs(z) < 5:
            x = random.uniform(-40, 40)
            z = random.uniform(-40, 40)
        
        vel_x = random.uniform(-0.2, 0.2)
        vel_z = random.uniform(-0.2, 0.2)
        rot_speed = random.uniform(-3, 3)
        asteroides.append(Asteroide(x, z, vel_x, vel_z, rot_speed))


def display():
    global nave_x, nave_y, nave_z, nave_angle, nave_vel_x, nave_vel_z, nave_accel
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    
    # Câmera acompanha a nave de cima
    gluLookAt(nave_x, 20.0, nave_z + 5.0,  # Posição da câmera
              nave_x, 0.0, nave_z,          # Para onde olha
              0.0, 1.0, 0.0)                # Up vector
    
    # Atualizar física da nave
    update_nave()
    
    # Desenhar a nave (carro)
    glPushMatrix()
    glTranslatef(nave_x, nave_y, nave_z)
    glRotatef(nave_angle, 0.0, 1.0, 0.0)
    glColor3f(0.0, 1.0, 0.0)  # Verde para a nave
    visualization.draw(carro)
    glPopMatrix()
    
    # Atualizar e desenhar asteroides
    for asteroide in asteroides:
        asteroide.update()
        glPushMatrix()
        glTranslatef(asteroide.x, 0.0, asteroide.z)
        glRotatef(asteroide.rotation, 1.0, 1.0, 1.0)
        glScalef(asteroide.size, asteroide.size, asteroide.size)
        glColor3f(0.8, 0.4, 0.2)  # Cor marrom para asteroides
        visualization.draw(roda)
        glPopMatrix()
    
    # Desenhar grid de referência
    draw_grid()
    
    glutSwapBuffers()

def update_nave():
    global nave_x, nave_z, nave_vel_x, nave_vel_z, nave_accel, nave_angle
    
    # Aplicar aceleração na direção que a nave está apontando
    if nave_accel != 0:
        angle_rad = math.radians(nave_angle)
        nave_vel_x += nave_accel * math.sin(angle_rad) * 0.1
        nave_vel_z += nave_accel * math.cos(angle_rad) * 0.1
    
    # Aplicar atrito
    nave_vel_x *= 0.98
    nave_vel_z *= 0.98
    
    # Limitar velocidade máxima
    max_vel = 0.8
    if abs(nave_vel_x) > max_vel:
        nave_vel_x = max_vel if nave_vel_x > 0 else -max_vel
    if abs(nave_vel_z) > max_vel:
        nave_vel_z = max_vel if nave_vel_z > 0 else -max_vel
    
    # Atualizar posição
    nave_x += nave_vel_x
    nave_z += nave_vel_z
    
    # Wrap around screen
    if nave_x > 50: nave_x = -50
    if nave_x < -50: nave_x = 50
    if nave_z > 50: nave_z = -50
    if nave_z < -50: nave_z = 50

def draw_grid():
    glColor3f(0.3, 0.3, 0.3)
    glBegin(GL_LINES)
    for i in range(-50, 51, 10):
        # Linhas verticais
        glVertex3f(i, 0.0, -50.0)
        glVertex3f(i, 0.0, 50.0)
        # Linhas horizontais
        glVertex3f(-50.0, 0.0, i)
        glVertex3f(50.0, 0.0, i)
    glEnd()
    
def Keys(key, x, y):
    global nave_angle, nave_accel
    
    if key == GLUT_KEY_LEFT:
        nave_angle += 5.0  # Girar para a esquerda
    elif key == GLUT_KEY_RIGHT:
        nave_angle -= 5.0  # Girar para a direita
    elif key == GLUT_KEY_DOWN:
        nave_accel = 1.0   # Acelerar para frente
    elif key == GLUT_KEY_UP:
        nave_accel = -0.5  # Acelerar para trás

def keyUp(key, x, y):
    global nave_accel
    if key == GLUT_KEY_UP or key == GLUT_KEY_DOWN:
        nave_accel = 0.0   # Parar aceleração quando soltar a tecla         
       
def animacao(value):
    glutPostRedisplay()
    glutTimerFunc(16, animacao, 1)  # ~60 FPS
    
def idle():
    pass
    
    
def resize(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60.0, w/h, 0.1, 200.0)  # Campo de visão maior e distância ajustada
    glMatrixMode(GL_MODELVIEW)

  

def init():
    glClearColor (0.3, 0.3, 0.3, 0.0)
    glShadeModel( GL_SMOOTH )
    glClearColor( 0.0, 0.1, 0.0, 0.5 )
    glClearDepth( 1.0 )
    glEnable( GL_DEPTH_TEST )
    glDepthFunc( GL_LEQUAL )
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST )

    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, [0.1, 0.1, 0.1, 1.0] )
    glLightfv( GL_LIGHT0, GL_AMBIENT, [ 0.2, 0.2, 0.2, 1.0] )
    glLightfv( GL_LIGHT0, GL_DIFFUSE, [0.5, 0.5, 0.5, 1.0] )
    glLightfv( GL_LIGHT0, GL_SPECULAR, [0.7, 0.7, 0.7, 1] );
    glLightfv( GL_LIGHT0, GL_POSITION, [10.0, 10.0, 10.0, 0.0])
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01)
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01)
    glEnable( GL_LIGHT0 )
    glEnable( GL_COLOR_MATERIAL )
    glShadeModel( GL_SMOOTH )
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE )
    glDepthFunc(GL_LEQUAL)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)

glutInit()
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB)
glutInitWindowSize(1920, 1080)
glutInitWindowPosition(100, 100)
wind = glutCreateWindow("Asteroids Game")
init()
init_asteroides()  # Inicializar asteroides
roda = pywavefront.Wavefront("roda2.obj")
carro = pywavefront.Wavefront("carro.obj")
glutDisplayFunc(display)
glutReshapeFunc(resize)
glutTimerFunc(16, animacao, 1)  # ~60 FPS
glutSpecialFunc(Keys)
glutSpecialUpFunc(keyUp)  # Callback para quando solta a tecla
glutMainLoop()
