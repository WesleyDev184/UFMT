from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import pywavefront
from pywavefront import visualization

T = 1
T2 = 1
T3 = 1


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    
    glPushMatrix()
    #Ações em todo o carro
    glRotatef(T, 0.0, 1.0, 0.0)
    glTranslatef(0, 0, T3)
    #glScalef(T, T2, T3)

    glPushMatrix()
    #Corpo do carro
    glTranslatef(0.0, 1.0, 0.0)
    glColor3f(0.1, 0.0, 1.1)
    visualization.draw(carro)
    glPopMatrix()

    glPushMatrix()
    glColor3f(1.0, 0.1, 0.1)
    glTranslatef(1.2, 1.0, 3.0)
    glRotatef(T2, 1.0, 0.0, 0.0)
    visualization.draw(roda)
    glPopMatrix()

    glPushMatrix()
    glColor3f(1.0, 0.1, 0.1)
    glTranslatef(-1.2, 1.0, 3.0)
    glRotatef(T2, 1.0, 0.0, 0.0)
    visualization.draw(roda)
    glPopMatrix()

    glPushMatrix()
    glColor3f(1.0, 0.1, 0.1)
    glTranslatef(1.2, 1.0, -3.0)
    glRotatef(T, 0.0, 1.0, 0.0)
    glRotatef(T2, 1.0, 0.0, 0.0)
    visualization.draw(roda)
    glPopMatrix()

    glPushMatrix()
    glColor3f(1.0, 0.1, 0.1)
    glTranslatef(-1.2, 1.0, -3.0)
    glRotatef(T, 0.0, 1.0, 0.0)
    glRotatef(T2, 1.0, 0.0, 0.0)
    visualization.draw(roda)
    glPopMatrix()

    glPopMatrix()
    
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

  
  


    glutSwapBuffers()
    
def Keys(key, x, y):
    global T
    global T2
    global T3
    
    if(key == GLUT_KEY_RIGHT ): 
        T -= 1 
    elif(key == GLUT_KEY_LEFT ): 
        T += 1 
    elif(key == GLUT_KEY_UP ): 
        T2 -= 5 
    elif(key == GLUT_KEY_DOWN ): 
        T2 += 5 
    elif(key == GLUT_KEY_PAGE_UP ): 
        T3 -= 1 
    elif(key == GLUT_KEY_PAGE_DOWN ): 
        T3 += 1         
       
def animacao(value):
    glutPostRedisplay()
    glutTimerFunc(30, animacao,1)
    global T
    
def idle():
    global T
    T -= 1
    
    
def resize(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(25.0, w/h, 1.0, 100.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(9.0, 12.0, 10.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0)

  

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
wind = glutCreateWindow("Cubo")
init()
roda = pywavefront.Wavefront("roda2.obj")
carro = pywavefront.Wavefront("carro.obj")
glutDisplayFunc(display)
glutReshapeFunc(resize)
glutTimerFunc(30,animacao,1)
glutSpecialFunc(Keys)
glutMainLoop()
