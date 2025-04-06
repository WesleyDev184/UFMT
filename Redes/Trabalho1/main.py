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

class App:
    def __init__(self):
        pyxel.init(231, 128, title="Tank Game", fps=30)

        pyxel.images[0] = pyxel.Image.from_image(
            "assets/urban_rpg.png", incl_colors=True
        )
        for i in range(3):
            pyxel.tilemaps[i] = pyxel.Tilemap.from_tmx("assets/mapa.tmx", i)

        self.player = (160, 80, 1, 0)  # (x, y, u, v)
        self.cars = [
            (128, 104, -2, 0),
            (288, 104, -2, 1),
            (416, 112, -2, 2),
            (32, 144, 2, 3),
            (64, 136, 2, 4),
            (96, 136, 2, 4),
        ]
        pyxel.run(self.update, self.draw)

    def update(self):
        # Reiniciar o jogo ao pressionar F5
        if pyxel.btnp(pyxel.KEY_F5):
            subprocess.Popen(
                f'"{sys.executable}" {" ".join([f"{arg}" for arg in sys.argv])}',
                shell=True,
            )
            sys.exit()

        # Update player
        x, y, u, v = self.player
        dx, dy = 0, 0
        if pyxel.btn(pyxel.KEY_UP):
            dy = -5
            u, v = 2, 1
        if pyxel.btn(pyxel.KEY_DOWN):
            dy = 5
            u, v = 1, 1
        if pyxel.btn(pyxel.KEY_LEFT):
            dx = -5
            u, v = 0, 1
        if pyxel.btn(pyxel.KEY_RIGHT):
            dx = 5
            u, v = 3, 1
        if v == 1:
            v += [-1, 0, -1, 1][pyxel.frame_count // 5 % 4]

        x, y = push_back(x, y, dx, dy)
        map_width = pyxel.tilemaps[0].width * 8
        map_height = pyxel.tilemaps[0].height * 8
        x = min(max(x, 0), map_width - 16)
        y = min(max(y, 0), map_height - 16)
        self.player = (x, y, u, v)

        # Update cars
        for i, car in enumerate(self.cars):
            x, y, dx, image = car
            x += dx
            if x <= -32:
                x = pyxel.tilemaps[0].width * 8
            elif x >= pyxel.tilemaps[0].width * 8:
                x = -32
            self.cars[i] = (x, y, dx, image)

    def draw(self):
        x, y, u, v = self.player
        cam_x = x - pyxel.width // 2 + 8
        cam_y = y - pyxel.height // 2 + 8
        map_width = pyxel.tilemaps[0].width * 8
        map_height = pyxel.tilemaps[0].height * 8
        cam_x = min(max(cam_x, 0), map_width - pyxel.width)
        cam_y = min(max(cam_y, 0), map_height - pyxel.height)
        pyxel.camera(cam_x, cam_y)
        pyxel.cls(1)
        pyxel.bltm(0, 0, 0, 0, 0, map_width, map_height, 0)
        pyxel.bltm(0, 0, 1, 0, 0, map_width, map_height, 0)
        pyxel.blt(
            x,
            y - 1,
            0,
            HUMAN_IMAGE[0] + u * 16,
            HUMAN_IMAGE[1] + v * 16,
            HUMAN_IMAGE[2],
            HUMAN_IMAGE[3],
            0,
        )
        pyxel.camera()


App()
