import pyxel
import sys
import subprocess  # Adicionado para reinício com F5

HUMAN_IMAGE = (368, 8, 16, 16)
CAR_IMAGES = [
    (240, 272, 32, 24),
    (240, 240, 32, 24),
    (336, 264, 32, 16),
    (336, 280, 32, 16),
    (288, 240, 32, 24),
]

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
            self.v += [-1,0,-1,1][pyxel.frame_count // 5 % 4]

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
        pyxel.init(231, 128, title="Tank Game", fps=30)

        pyxel.images[0] = pyxel.Image.from_image("assets/urban_rpg.png", incl_colors=True)
        for i in range(3):
            pyxel.tilemaps[i] = pyxel.Tilemap.from_tmx("assets/mapa.tmx", i)

        # Inicializa player e carros como objetos
        # self.player = Player(183, 10) #spawn 1
        # self.player = Player(15, 355) #spawn 2
        self.player = Player(512, 355) #spawn 3
        self.cars = [
            Car(128, 253, -2, 0),
            Car(288, 253, -2, 1),
            Car(416, 260, -2, 2),
            Car(32, 283, 2, 3),
            Car(64, 275, 2, 4),
            Car(96, 275, 2, 4),
        ]
        pyxel.run(self.update, self.draw)

    def update(self):
        # Reiniciar o jogo ao pressionar F5
        if pyxel.btnp(pyxel.KEY_F5):
            subprocess.Popen(
                f'"{sys.executable}" {" ".join([f"{arg}" for arg in sys.argv])}', shell=True
            )
            sys.exit()

        map_width = pyxel.tilemaps[0].width * 8
        map_height = pyxel.tilemaps[0].height * 8

        self.player.update(map_width, map_height)
        for car in self.cars:
            car.update(map_width)

    def draw(self):
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

        self.player.draw()
        for car in self.cars:
            car.draw()

        pyxel.camera()

App()