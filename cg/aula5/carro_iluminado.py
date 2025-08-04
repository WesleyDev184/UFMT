from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import pywavefront
from pywavefront import visualization

T = 0
T2 = 0
T3 = 0

light_position = [4.0, 7.0, 4.0, 1.0]

amb_light = [ 0.3, 0.3, 0.3, 1.0]
diffuse = [ 0.9, 0.9, 0.9, 1.0]
specular = [ 1.0, 1.0, 1.0, 1.0]
attenuation_quad = 0.01
attenuation_linear = 0.01


def display():
    global carro, roda
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    
    luz()
    
    

    ouro_amb = [0.24725, 0.1995, 0.0745, 1.0]
    ouro_dif = [0.75164, 0.60648, 0.22648, 1.0]
    ouro_spe = [0.628281, 0.555802, 0.366065, 1.0]
    ouro_shi = 0.4*128.0

    chrome_amb = [0.25, 0.25, 0.25, 1.0]
    chrome_dif = [0.4, 0.4, 0.4, 1.0]
    chrome_spe = [0.774597, 0.774597, 0.774597, 1.0]
    chrome_shi = 0.6*128.0

    rubi_amb = [0.1745, 0.01175, 0.01175, 1.0]
    rubi_dif = [0.61424, 0.04136, 0.04136, 1.0]
    rubi_spe = [0.727811, 0.626959, 0.626959, 1.0]
    rubi_shi = 1.0*128.0

    glPushMatrix()
    #Ações em todo o carro
    #glRotatef(T, 0.0, 1.0, 0.0)
    glRotatef(T2, 1.0, 0.0, 0.0)
    #glRotatef(T3, 0.0, 0.0, 1.0)
    glTranslatef(0.0, 0.0, T3)
    #glScalef(T, T2, T3)
    
    #glMaterialfv(GL_FRONT,GL_AMBIENT,rubi_amb)
    #glMaterialfv(GL_FRONT,GL_DIFFUSE,rubi_dif)
    #glMaterialfv(GL_FRONT,GL_SPECULAR,rubi_spe)
    #glMaterialf(GL_FRONT,GL_SHININESS,rubi_shi)
   
    
    carro.mesh_list[0].materials[0].ambient = rubi_amb
    carro.mesh_list[0].materials[0].diffuse = rubi_dif
    carro.mesh_list[0].materials[0].specular = rubi_spe
    carro.mesh_list[0].materials[0].shininess = rubi_shi

    glPushMatrix()
    #Corpo do carro
    glTranslatef(0.0, 1.0, 0.0)
    #glColor3f(0.0, 0.0, 1.0)
    visualization.draw(carro)
    glPopMatrix()
    
    
    roda.mesh_list[0].materials[0].ambient = chrome_amb
    roda.mesh_list[0].materials[0].diffuse = chrome_dif
    roda.mesh_list[0].materials[0].specular = chrome_spe
    roda.mesh_list[0].materials[0].shininess = chrome_shi
    
    #glEnable( GL_COLOR_MATERIAL )
    #glColor3f(0.7, 0.7, 0.1)

    glPushMatrix()
    #glColor3f(1.0, 0.0, 0.0)
    glTranslatef(1.2, 1.0, 3.0)
    #glRotatef(T, 0.0, -1.0, 0.0)
    visualization.draw(roda)
    glPopMatrix()

    glPushMatrix()
    #glColor3f(1.0, 0.0, 0.0)
    glTranslatef(-1.2, 1.0, 3.0)
    #glRotatef(T, 0.0, -1.0, 0.0)
    visualization.draw(roda)
    glPopMatrix()

    glPushMatrix()
    #glColor3f(1.0, 0.0, 0.0)
    glTranslatef(1.2, 1.0, -3.0)
    visualization.draw(roda)
    glPopMatrix()

    glPushMatrix()
    #glColor3f(1.0, 0.0, 0.0)
    glTranslatef(-1.2, 1.0, -3.0)
    visualization.draw(roda)
    glPopMatrix()

    glPopMatrix()
    
    glEnable(GL_COLOR_MATERIAL)
    
    glBegin(GL_LINES)
    glColor3f(1.0, 0.0, 0.0)
    glVertex3f(0.0, 0.0, 0.0)
    glVertex3f(10.0, 0.0, 0.0)
    glEnd()
    
    glBegin(GL_LINES)
    glColor3f(0.0, 1.0, 0.0)
    glVertex3f(0.0, 0.0, 0.0)
    glVertex3f(0.0, 10.0, 0.0)
    glEnd()
    
    glBegin(GL_LINES)
    glColor3f(0.0, 0.0, 1.0)
    glVertex3f(0.0, 0.0, 0.0)
    glVertex3f(0.0, 0.0, 10.0)
    glEnd()
    
    
    glPushMatrix()
    glColor3f(1.0,1.0,1.0)
    glTranslatef(light_position[0], light_position[1], light_position[2])
    glBegin(GL_TRIANGLES)
    glVertex3f(0.0, 0.0, 0.0)
    glVertex3f(0.1, 0.0, 0.0)
    glVertex3f(0.1, 0.1, 0.0)
    glEnd()
    glPopMatrix()
    
    glDisable(GL_COLOR_MATERIAL)
    
    

    glutSwapBuffers()
    
def Keys(key, x, y):
    global T
    global T2
    global T3
    
    if(key == GLUT_KEY_LEFT ): 
        #T -= 1 
        light_position[0] -= 1
    elif(key == GLUT_KEY_RIGHT ): 
        #T += 1 
        light_position[0] += 1
    elif(key == GLUT_KEY_UP ): 
        #T2 -= 1 
        light_position[2] -= 1
    elif(key == GLUT_KEY_DOWN ): 
        #T2 += 1 
        light_position[2] += 1
    elif(key == GLUT_KEY_PAGE_UP ): 
        T3 -= 1 
    elif(key == GLUT_KEY_PAGE_DOWN ): 
        T3 += 1         
        
        
def Keys_letras(key, x ,y):
    global amb_light, diffuse, specular, attenuation_linear, attenuation_quad
    delta = 0.3
    # Luz ambiente
    if(key == b'q' ):   #Q
        amb_light[0] += delta
    elif(key == b'a' ): #A
        amb_light[0] -= delta 
    elif(key == b'w' ): #W
        amb_light[1] += delta
    elif(key == b's' ): #S
        amb_light[1] -= delta
    elif(key == b'e' ): #E
        amb_light[2] += delta
    elif(key == b'd' ): #D
        amb_light[2] -= delta
        
        
    #luz difusa
    elif(key == b'r' ): #R
        diffuse[0] += delta 
    elif(key == b'f' ): #F
        diffuse[0] -= delta 
    elif(key == b't' ): #T
        diffuse[1] += delta
    elif(key == b'g' ): #G
        diffuse[1] -= delta
    elif(key == b'y' ): #Y
        diffuse[2] += delta
    elif(key == b'h' ): #H
        diffuse[2] -= delta
        
    
    #luz especular
    elif(key == b'u' ): #U
        specular[0] += delta
    elif(key == b'j' ): #J
        specular[0] -= delta
    elif(key == b'i' ): #I
        specular[1] += delta
    elif(key == b'k' ): #K
        specular[1] -= delta
    elif(key == b'o' ): #O
        specular[2] += delta
    elif(key == b'l' ): #L
        specular[2] -= delta
        
        
    elif(key == b'n' ): #N
        attenuation_quad += 0.001
    elif(key == b'm' ): #M
        attenuation_quad -= 0.001
        
        
        
        

    
        
    glutPostRedisplay()
       
def animacao(value):
    glutPostRedisplay()
    glutTimerFunc(30, animacao,1)
    
    
def resize(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(65.0, w/h, 1.0, 100.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(5.0, 8.0, 10.0,
                0.0, 2.0, 0.0,
                0.0, 1.0, 0.0)

  

def init():
    glClearColor (0.0, 0.0, 0.0, 0.0)
    glEnable( GL_DEPTH_TEST )
    glDepthFunc( GL_LESS )
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST )
    glEnable(GL_LIGHTING)
    glEnable( GL_LIGHT0 )
    #glEnable( GL_COLOR_MATERIAL ) # Transforma cores em materiais
    glShadeModel( GL_SMOOTH )  #Suaviza normais
    glEnable(GL_NORMALIZE)
    #glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE )
    
def luz():
    glLightfv(GL_LIGHT0, GL_POSITION, light_position)
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_light)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse)
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular)
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, attenuation_quad)
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, attenuation_linear)

glutInit()
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA)
glutInitWindowSize(1920, 1080)
glutInitWindowPosition(100, 100)
wind = glutCreateWindow("Cubo")
init()
luz()
roda = pywavefront.Wavefront("roda.obj", create_materials=True)
carro = pywavefront.Wavefront("carro.obj", create_materials=True)
glutDisplayFunc(display)
glutReshapeFunc(resize)
glutTimerFunc(30,animacao,1)
glutSpecialFunc(Keys)
glutKeyboardFunc(Keys_letras)
glutMainLoop()
