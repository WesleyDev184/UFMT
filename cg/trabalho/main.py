from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import pywavefront
from pywavefront import visualization
import random
import math
import sys

# Classe para o player (nave)
class Player:
    def __init__(self, x=0.0, y=0.0, z=0.0):
        self.x = x
        self.y = y
        self.z = z
        self.angle = 0.0
        self.vel_x = 0.0
        self.vel_z = 0.0
        self.accel = 0.0
        self.max_vel = 0.4
        self.friction = 0.93
        self.accel_strength = 0.05
        self.rotation_speed = 3.0
    
    def update(self, pressed_special, pressed_keys):
        # Controle por teclas simultâneas
        if GLUT_KEY_LEFT in pressed_special:
            self.angle += self.rotation_speed
        if GLUT_KEY_RIGHT in pressed_special:
            self.angle -= self.rotation_speed

        # teclas para frente/trás
        accel_input = 0.0
        if GLUT_KEY_DOWN in pressed_special or 's' in pressed_keys or 'S' in pressed_keys:
            accel_input = -0.5
        if GLUT_KEY_UP in pressed_special or 'w' in pressed_keys or 'W' in pressed_keys:
            accel_input = 0.5

        # Aplicar aceleração na direção que a nave está apontando
        if accel_input != 0:
            angle_rad = math.radians(self.angle)
            self.vel_x += accel_input * math.sin(angle_rad) * self.accel_strength
            self.vel_z += accel_input * math.cos(angle_rad) * self.accel_strength
        
        # Aplicar atrito
        self.vel_x *= self.friction
        self.vel_z *= self.friction
        
        # Limitar velocidade máxima
        if abs(self.vel_x) > self.max_vel:
            self.vel_x = self.max_vel if self.vel_x > 0 else -self.max_vel
        if abs(self.vel_z) > self.max_vel:
            self.vel_z = self.max_vel if self.vel_z > 0 else -self.max_vel
        
        # Atualizar posição
        self.x += self.vel_x
        self.z += self.vel_z
        
        # Constrain nave dentro do grid desenhado (±50)
        if self.x > 50: self.x = 50
        if self.x < -50: self.x = -50
        if self.z > 50: self.z = 50
        if self.z < -50: self.z = -50
    
    def draw(self, player_model):
        glPushMatrix()
        glTranslatef(self.x, self.y, self.z)
        glRotatef(self.angle, 0.0, 1.0, 0.0)
        glRotatef(180.0, 0.0, 1.0, 0.0)  # Rotaciona 180 graus para inverter frente/trás
        glScalef(0.3, 0.3, 0.3)  # Diminui o tamanho da nave
        glColor3f(1.0, 1.0, 1.0)  # Branco para a (galinha)
        visualization.draw(player_model)
        glPopMatrix()
    
    def shoot(self):
        angle_rad = math.radians(self.angle)
        dir_x = math.sin(angle_rad)
        dir_z = math.cos(angle_rad)
        return Projetil(self.x, self.z, dir_x, dir_z)

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
        self.mass = self.size  # massa proporcional ao tamanho
    
    def update(self):
        self.x += self.vel_x
        self.z += self.vel_z
        self.rotation += self.rot_speed
    
    def collides_with(self, other):
        distance = math.hypot(self.x - other.x, self.z - other.z)
        return distance < (self.size + other.size)
    
    def resolve_collision(self, other):
        # Calcular vetor de direção entre os asteroides
        dx = other.x - self.x
        dz = other.z - self.z
        distance = math.hypot(dx, dz)
        
        if distance == 0 or distance < 0.1:
            # Evitar divisão por zero - usar direção aleatória
            dx = random.uniform(-1, 1)
            dz = random.uniform(-1, 1)
            distance = math.hypot(dx, dz)
        
        # Normalizar o vetor de direção
        nx = dx / distance
        nz = dz / distance
        
        # Separar os asteroides se estiverem sobrepostos
        overlap = (self.size + other.size) - distance
        if overlap > 0:
            separation = (overlap / 2.0) + 0.1  # Adicionar uma pequena margem extra
            self.x -= nx * separation
            self.z -= nz * separation
            other.x += nx * separation
            other.z += nz * separation
        
        # Sistema de colisão mais simples e efetivo
        # Salvar velocidades originais
        vel1_x, vel1_z = self.vel_x, self.vel_z
        vel2_x, vel2_z = other.vel_x, other.vel_z
        
        # Coeficiente de restituição (quão "bouncy" é a colisão)
        bounce = 1.2
        
        # Troca de velocidades com base na massa e direção da colisão
        # Calcular componentes da velocidade na direção da colisão
        v1_normal = vel1_x * nx + vel1_z * nz
        v2_normal = vel2_x * nx + vel2_z * nz
        
        # Calcular componentes perpendiculares (tangenciais)
        v1_tang_x = vel1_x - v1_normal * nx
        v1_tang_z = vel1_z - v1_normal * nz
        v2_tang_x = vel2_x - v2_normal * nx
        v2_tang_z = vel2_z - v2_normal * nz
        
        # Calcular novas velocidades normais após colisão
        mass_sum = self.mass + other.mass
        new_v1_normal = ((self.mass - other.mass) * v1_normal + 2 * other.mass * v2_normal) / mass_sum
        new_v2_normal = ((other.mass - self.mass) * v2_normal + 2 * self.mass * v1_normal) / mass_sum
        
        # Aplicar coeficiente de restituição
        new_v1_normal *= bounce
        new_v2_normal *= bounce
        
        # Recombinar componentes normais e tangenciais
        self.vel_x = new_v1_normal * nx + v1_tang_x
        self.vel_z = new_v1_normal * nz + v1_tang_z
        other.vel_x = new_v2_normal * nx + v2_tang_x
        other.vel_z = new_v2_normal * nz + v2_tang_z
        
        # Adicionar um pouco de variação aleatória para tornar mais interessante
        random_factor = 0.1
        self.vel_x += random.uniform(-random_factor, random_factor)
        self.vel_z += random.uniform(-random_factor, random_factor)
        other.vel_x += random.uniform(-random_factor, random_factor)
        other.vel_z += random.uniform(-random_factor, random_factor)
        
        # Limitar velocidades para evitar que fiquem muito rápidas
        max_speed = 0.1
        self_speed = math.hypot(self.vel_x, self.vel_z)
        other_speed = math.hypot(other.vel_x, other.vel_z)
        
        if self_speed > max_speed:
            self.vel_x = (self.vel_x / self_speed) * max_speed
            self.vel_z = (self.vel_z / self_speed) * max_speed
            
        if other_speed > max_speed:
            other.vel_x = (other.vel_x / other_speed) * max_speed
            other.vel_z = (other.vel_z / other_speed) * max_speed
        
        # Adicionar um pouco de rotação aleatória após colisão
        self.rot_speed += random.uniform(-2, 2)
        other.rot_speed += random.uniform(-2, 2)

# Lista de asteroides
asteroides = []

# Quantidade base de asteroides
BASE_ASTEROIDES = 12
SAFE_SPAWN_DIST = 8.0  # distância mínima do jogador para spawn

# Projetil (tiros da nave)
class Projetil:
    def __init__(self, x, z, dir_x, dir_z):
        self.x = x
        self.z = z
        self.dir_x = dir_x
        self.dir_z = dir_z
        self.speed = 1.5
        self.life = 120  # frames

    def update(self):
        self.x += self.dir_x * self.speed
        self.z += self.dir_z * self.speed
        self.life -= 1

    def offscreen(self):
        return abs(self.x) > 50 or abs(self.z) > 50 or self.life <= 0


# Lista de projeteis
projeteis = []

# Classe para partículas de explosão
class Particula:
    def __init__(self, x, z):
        self.x = x
        self.z = z
        self.vel_x = random.uniform(-0.3, 0.3)
        self.vel_z = random.uniform(-0.3, 0.3)
        self.vel_y = random.uniform(0.1, 0.4)
        self.y = 0.0
        self.life = 60  # frames de vida
        self.max_life = 60
        self.size = random.uniform(0.05, 0.15) 
        fire_type = random.choice(['yellow', 'orange', 'red'])
        if fire_type == 'yellow':
            self.r = random.uniform(1.0, 1.0)    # Amarelo brilhante
            self.g = random.uniform(0.8, 1.0)
            self.b = random.uniform(0.0, 0.3)
        elif fire_type == 'orange':
            self.r = random.uniform(1.0, 1.0)    # Laranja
            self.g = random.uniform(0.4, 0.7)
            self.b = random.uniform(0.0, 0.1)
        else:  # red
            self.r = random.uniform(0.8, 1.0)    # Vermelho
            self.g = random.uniform(0.1, 0.3)
            self.b = random.uniform(0.0, 0.1)
    
    def update(self):
        self.x += self.vel_x
        self.z += self.vel_z
        self.y += self.vel_y
        self.vel_y -= 0.02  # gravidade
        self.life -= 1
        
        # Transição de cores de fogo (amarelo -> laranja -> vermelho -> preto)
        life_ratio = self.life / self.max_life
        if life_ratio > 0.7:
            # Fase inicial: amarelo brilhante
            self.r = 1.0
            self.g = 1.0 * life_ratio
            self.b = 0.1
        elif life_ratio > 0.4:
            # Fase média: laranja
            self.r = 1.0
            self.g = 0.5 * life_ratio
            self.b = 0.05
        elif life_ratio > 0.1:
            # Fase final: vermelho
            self.r = 0.9 * life_ratio
            self.g = 0.1 * life_ratio
            self.b = 0.0
        else:
            # Fade final para preto
            fade = life_ratio * 10  # amplifica o fade final
            self.r *= fade
            self.g *= fade
            self.b *= fade
    
    def is_dead(self):
        return self.life <= 0 or self.y < 0

# Lista de partículas
particulas = []

# Instância do player
player = Player()

# Pontuação
score = 0

# Conjuntos para teclas pressionadas (suportar múltiplas simultâneas)
pressed_special = set()   # guarda códigos de teclas especiais (GLUT_KEY_*)
pressed_keys = set()      # guarda teclas ASCII (strings)

# Inicializar asteroides
def init_asteroides():
    global asteroides
    for i in range(BASE_ASTEROIDES):
        # tentar encontrar uma posição segura para spawn
        attempts = 0
        x = random.uniform(-40, 40)
        z = random.uniform(-40, 40)
        while math.hypot(player.x - x, player.z - z) < SAFE_SPAWN_DIST and attempts < 20:
            x = random.uniform(-40, 40)
            z = random.uniform(-40, 40)
            attempts += 1

        # Velocidade apontando para a nave
        dx = player.x - x
        dz = player.z - z
        d = math.hypot(dx, dz)
        if d == 0:
            d = 1.0
        speed = random.uniform(0.01, 0.06)
        vel_x = (dx / d) * speed
        vel_z = (dz / d) * speed
        rot_speed = random.uniform(-3, 3)
        asteroides.append(Asteroide(x, z, vel_x, vel_z, rot_speed))


def spawn_asteroide_from_opposite(dir_x, dir_z):
    """Cria um asteroide vindo da direção oposta dada a direção (dir_x, dir_z)."""
    # Spawn numa borda oposta (multiplica por -1 e posiciona perto da borda)
    if abs(dir_x) > abs(dir_z):
        # Movimento mais horizontal
        x = -50 if dir_x > 0 else 50
        z = random.uniform(-40, 40)
    else:
        # Movimento mais vertical (profundidade)
        z = -50 if dir_z > 0 else 50
        x = random.uniform(-40, 40)
    # garantir distancia segura
    attempts = 0
    while math.hypot(player.x - x, player.z - z) < SAFE_SPAWN_DIST and attempts < 20:
        # deslocar ao longo da borda
        if abs(x) == 50:
            z = random.uniform(-40, 40)
        else:
            x = random.uniform(-40, 40)
        attempts += 1

    # definir velocidade apontando para o centro (ou aproximado)
    # calcular velocidade apontando para a nave
    dx = player.x - x
    dz = player.z - z
    mag = math.hypot(dx, dz)
    if mag == 0:
        mag = 1.0
    speed = random.uniform(0.01, 0.06)
    vel_x = (dx / mag) * speed
    vel_z = (dz / mag) * speed
    rot_speed = random.uniform(-3, 3)
    asteroides.append(Asteroide(x, z, vel_x, vel_z, rot_speed))


def spawn_asteroide_safe():
    """Spawna um asteroide em posição segura (longe do jogador)."""
    attempts = 0
    max_attempts = 50
    
    while attempts < max_attempts:
        # Escolher uma posição aleatória no mapa
        x = random.uniform(-45, 45)
        z = random.uniform(-45, 45)
        
        # Verificar se está longe o suficiente do jogador
        dist_to_player = math.hypot(player.x - x, player.z - z)
        if dist_to_player >= SAFE_SPAWN_DIST:
            # Posição segura encontrada, calcular velocidade em direção ao jogador
            dx = player.x - x
            dz = player.z - z
            d = math.hypot(dx, dz)
            if d == 0:
                d = 1.0
            speed = random.uniform(0.01, 0.06)
            vel_x = (dx / d) * speed
            vel_z = (dz / d) * speed
            rot_speed = random.uniform(-3, 3)
            asteroides.append(Asteroide(x, z, vel_x, vel_z, rot_speed))
            return
        
        attempts += 1
    
    # Se não conseguir encontrar posição segura, spawnar na borda
    spawn_asteroide_from_opposite(random.uniform(-1, 1), random.uniform(-1, 1))


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    
    # Câmera acompanha a nave de cima
    gluLookAt(player.x, 20.0, player.z + 5.0,  # Posição da câmera
              player.x, 0.0, player.z,          # Para onde olha
              0.0, 1.0, 0.0)                    # Up vector
    
    # Atualizar física da nave
    player.update(pressed_special, pressed_keys)
    
    # Desenhar a nave (player)
    player.draw(nave)
    
    # Atualizar asteroides
    for asteroide in asteroides:
        asteroide.update()

    # Detectar e resolver colisões entre asteroides
    for i in range(len(asteroides)):
        for j in range(i + 1, len(asteroides)):
            if asteroides[i].collides_with(asteroides[j]):
                asteroides[i].resolve_collision(asteroides[j])

    # Desenhar asteroides (usar cópia para permitir remoção)
    for asteroide in list(asteroides):
        # Se saiu da visão (fora do grid desenhado ±50), remova e gere um novo
        if abs(asteroide.x) > 50 or abs(asteroide.z) > 50:
            try:
                asteroides.remove(asteroide)
                # Spawnar um novo asteroide em posição segura
                spawn_asteroide_safe()
            except ValueError:
                pass
            continue

        glPushMatrix()
        glTranslatef(asteroide.x, 0.0, asteroide.z)
        glRotatef(asteroide.rotation, 1.0, 1.0, 1.0)
        glScalef(asteroide.size, asteroide.size, asteroide.size)
        glColor3f(0.2, 0.4, 0.8)  # Tons de azul para asteroides
        visualization.draw(meteor)
        glPopMatrix()

    # Atualizar e desenhar projeteis
    for proj in list(projeteis):
        proj.update()
        # remover se fora
        if proj.offscreen():
            try:
                projeteis.remove(proj)
            except ValueError:
                pass
            continue

        glPushMatrix()
        glTranslatef(proj.x, 0.5, proj.z)
        glColor3f(1.0, 0.2, 0.0)  # Vermelho fogo ardente
        
        # Desenhar um círculo preenchido
        glBegin(GL_TRIANGLE_FAN)
        glVertex3f(0.0, 0.0, 0.0)  # Centro do círculo
        num_segments = 16
        radius = 0.3  # Raio do círculo
        for i in range(num_segments + 1):
            angle = 2.0 * math.pi * i / num_segments
            x = radius * math.cos(angle)
            z = radius * math.sin(angle)
            glVertex3f(x, 0.0, z)
        glEnd()
        
        glPopMatrix()

    # Atualizar e desenhar partículas de explosão
    for particula in list(particulas):
        particula.update()
        if particula.is_dead():
            try:
                particulas.remove(particula)
            except ValueError:
                pass
            continue
        
        glPushMatrix()
        glTranslatef(particula.x, particula.y, particula.z)
        glColor3f(particula.r, particula.g, particula.b)
        
        # Desenhar partícula como um círculo pequeno
        glBegin(GL_TRIANGLE_FAN)
        glVertex3f(0.0, 0.0, 0.0)  # Centro do círculo
        num_segments = 8  # Poucos segmentos para performance
        radius = particula.size
        for i in range(num_segments + 1):
            angle = 2.0 * math.pi * i / num_segments
            x = radius * math.cos(angle)
            z = radius * math.sin(angle)
            glVertex3f(x, 0.0, z)
        glEnd()
        
        glPopMatrix()

    # Colisões: projétil x asteroide
    global score
    for proj in list(projeteis):
        for asteroide in list(asteroides):
            dist = math.hypot(proj.x - asteroide.x, proj.z - asteroide.z)
            if dist < (asteroide.size * 1.2 + 0.5):
                # colisão: criar partículas de explosão
                num_particulas = int(20 + asteroide.size * 10)  # Mais partículas para asteroides maiores
                for i in range(num_particulas):
                    particula = Particula(asteroide.x, asteroide.z)
                    particulas.append(particula)
                
                # remover ambos, incrementar score e spawn de reposição
                try:
                    projeteis.remove(proj)
                except ValueError:
                    pass
                try:
                    asteroides.remove(asteroide)
                    # Spawnar um novo asteroide imediatamente em posição segura
                    spawn_asteroide_safe()
                except ValueError:
                    pass
                score += 1
                break

    # Manter quantidade fixa de asteroides (BASE_ASTEROIDES)
    while len(asteroides) < BASE_ASTEROIDES:
        spawn_asteroide_safe()

    # Desenhar HUD (pontuação)
    # posição em pixels (canto superior esquerdo)
    draw_text(10, glGetIntegerv(GL_VIEWPORT)[3] - 24, f"Score: {score}")
    
    # Desenhar grid de referência
    draw_grid()
    
    glutSwapBuffers()


def draw_grid():
    glColor3f(0.2, 0.3, 0.7)  # Grid azul
    glBegin(GL_LINES)
    for i in range(-50, 51, 10):
        # Linhas verticais
        glVertex3f(i, 0.0, -50.0)
        glVertex3f(i, 0.0, 50.0)
        # Linhas horizontais
        glVertex3f(-50.0, 0.0, i)
        glVertex3f(50.0, 0.0, i)
    glEnd()


def draw_text(x, y, text):
    # Tenta desenhar texto usando uma fonte bitmap do GLUT; se não disponível, printa no console
    try:
        # tenta recuperar uma fonte do módulo GLUT sem referenciar nomes que não existem
        glut_mod = sys.modules.get('OpenGL.GLUT')
        font = None
        if glut_mod is not None:
            font = getattr(glut_mod, 'GLUT_BITMAP_HELVETICA_18', None) or getattr(glut_mod, 'GLUT_BITMAP_8_BY_13', None)

        if font is None:
            # sem fonte disponível, cair para console
            raise RuntimeError('GLUT bitmap font not available')

        # salvar matrizes
        glMatrixMode(GL_PROJECTION)
        glPushMatrix()
        glLoadIdentity()
        viewport = glGetIntegerv(GL_VIEWPORT)
        gluOrtho2D(0, viewport[2], 0, viewport[3])
        glMatrixMode(GL_MODELVIEW)
        glPushMatrix()
        glLoadIdentity()
        glColor3f(1.0, 1.0, 1.0)
        glRasterPos2f(x, y)
        for ch in text:
            glutBitmapCharacter(font, ord(ch))
        glPopMatrix()
        glMatrixMode(GL_PROJECTION)
        glPopMatrix()
        glMatrixMode(GL_MODELVIEW)
    except Exception:
        # fallback: imprimir no console
        print(text)

def special_down(key, x, y):
    # adiciona tecla especial ao conjunto
    pressed_special.add(key)

def special_up(key, x, y):
    # remove tecla especial do conjunto
    try:
        pressed_special.remove(key)
    except KeyError:
        pass
    


def keyboard(key, x, y):
    global projeteis
    try:
        k = key.decode('utf-8')
    except Exception:
        k = key
    pressed_keys.add(k)
    if k == ' ':
        proj = player.shoot()
        projeteis.append(proj)

def keyboard_up(key, x, y):
    try:
        k = key.decode('utf-8')
    except Exception:
        k = key
    try:
        pressed_keys.remove(k)
    except KeyError:
        pass

def keyUp(key, x, y):
    special_up(key, x, y)
       
def animacao(value):
    glutPostRedisplay()
    glutTimerFunc(16, animacao, 1)  
    
def idle():
    pass
    
    
def resize(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60.0, w/h, 0.1, 200.0) 
    glMatrixMode(GL_MODELVIEW)

  

def init():
    glClearColor (0.05, 0.05, 0.1, 0.0)  
    glShadeModel( GL_SMOOTH )
    glClearColor( 0.05, 0.05, 0.1, 0.5 )  
    glClearDepth( 1.0 )
    glEnable( GL_DEPTH_TEST )
    glDepthFunc( GL_LEQUAL )
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST )

    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, [0.1, 0.1, 0.1, 1.0] )
    glLightfv( GL_LIGHT0, GL_AMBIENT, [ 0.2, 0.2, 0.2, 1.0] )
    glLightfv( GL_LIGHT0, GL_DIFFUSE, [0.25, 0.25, 0.25, 1.0] )  
    glLightfv( GL_LIGHT0, GL_SPECULAR, [0.35, 0.35, 0.35, 1] ); 
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
wind = glutCreateWindow("Game")
init()
init_asteroides()  # Inicializar asteroides
meteor = pywavefront.Wavefront("meteor.obj")
nave = pywavefront.Wavefront("galinha.obj")
glutDisplayFunc(display)
glutReshapeFunc(resize)
glutTimerFunc(16, animacao, 1)  # ~60 FPS
glutSpecialFunc(special_down)
glutSpecialUpFunc(special_up)  # Callback para quando solta a tecla especial
glutKeyboardFunc(keyboard)
glutKeyboardUpFunc(keyboard_up)
glutMainLoop()
