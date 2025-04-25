import random
import pyxel
from multplayer import MultiplayerClient

# Constantes e imagens
HUMAN_IMAGE = (368, 8, 16, 16)
CAR_IMAGES = [
    (240, 272, 32, 24),
    (240, 240, 32, 24),
    (336, 264, 32, 16),
    (336, 280, 32, 16),
    (288, 240, 32, 24),
]

# Função para detecção de colisão
def is_colliding(x, y):
    x1 = pyxel.floor(x) // 8
    y1 = pyxel.floor(y) // 8
    x2 = (pyxel.ceil(x) + 15) // 8
    y2 = (pyxel.ceil(y) + 15) // 8
    for yi in range(y1, y2 + 1):
        for xi in range(x1, x2 + 1):
            if pyxel.tilemaps[2].pget(xi, yi) == (2, 0):
                return True
    return False

# Função para empurrar de volta em caso de colisão
def push_back(x, y, dx, dy):
    for _ in range(pyxel.ceil(abs(dy))):
        step = max(-1, min(1, dy))
        if is_colliding(x, y + step):
            break
        y += step
        dy -= step
    for _ in range(pyxel.ceil(abs(dx))):
        step = max(-1, min(1, dx))
        if is_colliding(x + step, y):
            break
        x += step
        dx -= step
    return x, y

class Player:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.u = 1
        self.v = 0

    def update(self, map_width, map_height):
        dx, dy = 0, 0
        if pyxel.btn(pyxel.KEY_UP):
            dy = -5
            self.u, self.v = 2, 1
        if pyxel.btn(pyxel.KEY_DOWN):
            dy = 5
            self.u, self.v = 1, 1
        if pyxel.btn(pyxel.KEY_LEFT):
            dx = -5
            self.u, self.v = 0, 1
        if pyxel.btn(pyxel.KEY_RIGHT):
            dx = 5
            self.u, self.v = 3, 1
        if self.v == 1:
            self.v += [-1, 0, -1, 1][pyxel.frame_count // 5 % 4]

        new_x, new_y = push_back(self.x, self.y, dx, dy)
        new_x = min(max(new_x, 0), map_width - 16)
        new_y = min(max(new_y, 0), map_height - 16)
        self.x = new_x
        self.y = new_y

    def draw(self):
        pyxel.blt(
            self.x,
            self.y - 1,
            0,
            HUMAN_IMAGE[0] + self.u * 16,
            HUMAN_IMAGE[1] + self.v * 16,
            HUMAN_IMAGE[2],
            HUMAN_IMAGE[3],
            0,
        )

class Bullet:
    def __init__(self, x, y, dx, dy):
        self.x = x
        self.y = y
        self.dx = dx
        self.dy = dy
        self.active = True

    def update(self, map_width, map_height):
        self.x += self.dx
        self.y += self.dy
        if self.x < 0 or self.y < 0 or self.x > map_width or self.y > map_height:
            self.active = False

    def draw(self):
        pyxel.circ(self.x, self.y, 2, pyxel.COLOR_YELLOW)

class Car:
    def __init__(self, x, y, dx, image):
        self.x = x
        self.y = y
        self.dx = dx
        self.image = image

    def update(self, map_width):
        self.x += self.dx
        if self.x <= -32:
            self.x = map_width
        elif self.x >= map_width:
            self.x = -32

    def draw(self):
        u, v, w, h = CAR_IMAGES[self.image]
        pyxel.blt(self.x, self.y, 0, u, v, w, h, 0)

class App:
    def __init__(self):
        # Define o estado inicial do jogo
        self.game_state = "inicio"  # "inicio" ou "jogando"

        # Inicializa multiplayer
        self.mp_client = MultiplayerClient()

        # Dicionário para armazenar jogadores remotos e balas
        self.remote_players = {}
        self.bullets = []
        self.remote_bullets = {}

        self.shoot_cooldown = 0
        self.player_status = "vivo"
        self.spawns = [(183, 10), (15, 355), (512, 355)]

        pyxel.init(231, 128, title="Tank Game", fps=30)
        pyxel.images[0] = pyxel.Image.from_image("assets/urban_rpg.png", incl_colors=True)
        for i in range(3):
            pyxel.tilemaps[i] = pyxel.Tilemap.from_tmx("assets/mapa.tmx", i)

        spawn_x, spawn_y = random.choice(self.spawns)
        self.player = Player(spawn_x, spawn_y)
        
        self.cars = [
            Car(128, 253, -2, 0),
            Car(288, 253, -2, 1),
            Car(416, 260, -2, 2),
            Car(32, 283, 2, 3),
            Car(64, 275, 2, 4),
            Car(96, 275, 2, 4),
        ]
        pyxel.run(self.update, self.draw)

    def revive(self):
        spawn_x, spawn_y = random.choice(self.spawns)
        self.player = Player(spawn_x, spawn_y)
        self.bullets.clear()
        self.player_status = "vivo"
        self.mp_client.send_player_state(
            int(self.player.x),
            int(self.player.y),
            u=self.player.u,
            v=self.player.v,
            status=self.player_status,
            bullets=[]
        )

    def check_player_hit(self, bullet):
        if (self.player.x < bullet.x < self.player.x + 16) and (self.player.y < bullet.y < self.player.y + 16):
            return True
        return False

    def update(self):
        # Tela inicial: aguarda o início do jogo
        if self.game_state == "inicio":
            if pyxel.btnp(pyxel.KEY_SPACE):
                self.game_state = "jogando"
            return

        if pyxel.btnp(pyxel.KEY_F5):
            import sys, subprocess
            subprocess.Popen(
                f'"{sys.executable}" {" ".join(sys.argv)}', shell=True
            )
            sys.exit()

        map_width = pyxel.tilemaps[0].width * 8
        map_height = pyxel.tilemaps[0].height * 8

        if self.player_status == "morto":
            if pyxel.btnp(pyxel.MOUSE_BUTTON_LEFT):
                mx, my = pyxel.mouse_x, pyxel.mouse_y
                button_x = (pyxel.width - 80) // 2
                button_y = (pyxel.height - 20) // 2 + 20
                if button_x <= mx <= button_x + 80 and button_y <= my <= button_y + 20:
                    self.revive()
            return

        self.player.update(map_width, map_height)
        for car in self.cars:
            car.update(map_width)

        if self.shoot_cooldown > 0:
            self.shoot_cooldown -= 1

        if pyxel.btnp(pyxel.KEY_SPACE) and self.shoot_cooldown == 0:
            if self.player.u == 0:
                dx, dy = -10, 0
            elif self.player.u == 1:
                dx, dy = 0, 10
            elif self.player.u == 2:
                dx, dy = 0, -10
            elif self.player.u == 3:
                dx, dy = 10, 0
            else:
                dx, dy = 0, 0
            self.bullets.append(Bullet(self.player.x + 8, self.player.y + 8, dx, dy))
            self.shoot_cooldown = 30

        for bullet in self.bullets:
            bullet.update(map_width, map_height)
        self.bullets = [b for b in self.bullets if b.active]

        self.mp_client.send_player_state(
            int(self.player.x),
            int(self.player.y),
            u=self.player.u,
            v=self.player.v,
            status=self.player_status,
            bullets=[{"x": b.x, "y": b.y, "dx": b.dx, "dy": b.dy} for b in self.bullets]
        )

        for pid, pdata in self.mp_client.players.items():
            if pid != self.mp_client.player_id:
                if pid not in self.remote_players:
                    self.remote_players[pid] = Player(pdata["x"], pdata["y"])
                else:
                    remote_player = self.remote_players[pid]
                    remote_player.x = pdata["x"]
                    remote_player.y = pdata["y"]
                    remote_player.u = pdata.get("u", remote_player.u)
                    remote_player.v = pdata.get("v", remote_player.v)
                self.remote_bullets[pid] = [Bullet(b["x"], b["y"], b["dx"], b["dy"]) for b in pdata.get("bullets", [])]

        for bullets in self.remote_bullets.values():
            for bullet in bullets:
                if self.check_player_hit(bullet):
                    self.player_status = "morto"
                    break
            if self.player_status == "morto":
                break

    def draw(self):
        if self.game_state == "inicio":
            pyxel.cls(0)
            text = "Press SPACE to start"
            pyxel.text((pyxel.width - len(text)*4) // 2, pyxel.height // 2, text, pyxel.COLOR_WHITE)
            return

        cam_x = self.player.x - pyxel.width // 2 + 8
        cam_y = self.player.y - pyxel.height // 2 + 8
        map_width = pyxel.tilemaps[0].width * 8
        map_height = pyxel.tilemaps[0].height * 8
        cam_x = min(max(cam_x, 0), map_width - pyxel.width)
        cam_y = min(max(cam_y, 0), map_height - pyxel.height)
        pyxel.camera(cam_x, cam_y)
        pyxel.cls(1)
        pyxel.bltm(0, 0, 0, 0, 0, map_width, map_height, 0)
        pyxel.bltm(0, 0, 1, 0, 0, map_width, map_height, 0)
        
        for car in self.cars:
            car.draw()
        for bullet in self.bullets:
            bullet.draw()
        for _, remote_player in self.remote_players.items():
            remote_player.draw()
        for bullets in self.remote_bullets.values():
            for bullet in bullets:
                bullet.draw()

        pyxel.camera()

        if self.player_status == "morto":
            pyxel.cls(0)
            pyxel.text((pyxel.width // 2) - 30, (pyxel.height // 2) - 20, "GAME OVER", pyxel.COLOR_RED)
            button_x = (pyxel.width - 80) // 2
            button_y = (pyxel.height - 20) // 2 + 20
            pyxel.rect(button_x, button_y, 80, 20, pyxel.COLOR_GRAY)
            pyxel.rectb(button_x, button_y, 80, 20, pyxel.COLOR_WHITE)
            pyxel.text(button_x + 15, button_y + 7, "Reviver", pyxel.COLOR_WHITE)

App() 