import random
import pyxel
from multplayer import MultiplayerClient

# -------------------------------
# Constantes e recursos visuais
# -------------------------------
HUMAN_IMAGE = (368, 8, 16, 16)
CAR_IMAGES = [
    (240, 272, 32, 24),
    (240, 240, 32, 24),
    (336, 264, 32, 16),
    (336, 280, 32, 16),
    (288, 240, 32, 24),
]

# ----------------------------------
# Funcoes utilitarias de colisao
# ----------------------------------
def is_colliding(x, y):
    """Verifica colisao com tiles do mapa de colisao (tilemap 2)."""
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
    """Ajusta a posicao do jogador caso haja colisao com o mapa."""
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

# -------------------------------
# Classe do jogador local
# -------------------------------
class Player:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.u = 1  # direção
        self.v = 0  # animação
        self.status = "vivo"  # 'vivo' ou 'morto'
        self.score = 0       # score do player

    def update(self, map_width, map_height):
        dx, dy = 0, 0
        if pyxel.btn(pyxel.KEY_W):
            dy = -5
            self.u, self.v = 2, 1
        if pyxel.btn(pyxel.KEY_S):
            dy = 5
            self.u, self.v = 1, 1
        if pyxel.btn(pyxel.KEY_A):
            dx = -5
            self.u, self.v = 0, 1
        if pyxel.btn(pyxel.KEY_D):
            dx = 5
            self.u, self.v = 3, 1

        # Animação
        if self.v == 1:
            self.v += [-1, 0, -1, 1][pyxel.frame_count // 5 % 4]

        new_x, new_y = push_back(self.x, self.y, dx, dy)
        self.x = min(max(new_x, 0), map_width - 16)
        self.y = min(max(new_y, 0), map_height - 16)

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

# -------------------------------
# Classe de projeteis
# -------------------------------
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

# -------------------------------
# Classe de carros no mapa
# -------------------------------
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

# -------------------------------
# Classe principal do jogo
# -------------------------------
class App:
    def __init__(self):
        self.game_state = "inicio"
        self.mp_client = MultiplayerClient()
        self.remote_players = {}
        self.remote_bullets = {}
        self.bullets = []
        self.shoot_cooldown = 0
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
        self.mp_client.send_player_state(
            int(self.player.x), int(self.player.y),
            u=self.player.u, v=self.player.v,
            status=self.player.status,
            bullets=[],
            score=self.player.score
        )

    def check_player_hit(self, bullet):
        return (self.player.x < bullet.x < self.player.x + 16) and \
               (self.player.y < bullet.y < self.player.y + 16)

    def update(self):
        if self.game_state == "inicio":
            if pyxel.btnp(pyxel.KEY_SPACE):
                self.game_state = "jogando"
            return

        if pyxel.btnp(pyxel.KEY_F5):
            import sys, subprocess
            subprocess.Popen(f'"{sys.executable}" {" ".join(sys.argv)}', shell=True)
            sys.exit()

        map_width = pyxel.tilemaps[0].width * 8
        map_height = pyxel.tilemaps[0].height * 8

        if self.player.status == "morto":
            if pyxel.btnp(pyxel.KEY_RETURN):
                self.revive()
            return

        self.player.update(map_width, map_height)
        for car in self.cars:
            car.update(map_width)

        if self.shoot_cooldown > 0:
            self.shoot_cooldown -= 1

        if pyxel.btnp(pyxel.KEY_SPACE) and self.shoot_cooldown == 0:
            directions = [(-10, 0), (0, 10), (0, -10), (10, 0)]
            dx, dy = directions[self.player.u] if self.player.u < 4 else (0, 0)
            self.bullets.append(Bullet(self.player.x + 8, self.player.y + 8, dx, dy))
            self.shoot_cooldown = 30

        for bullet in self.bullets:
            bullet.update(map_width, map_height)
        self.bullets = [b for b in self.bullets if b.active]

        # Verifica colisão da bala com jogadores remotos:
        for bullet in self.bullets:
            for pid, remote_player in self.remote_players.items():
                if (remote_player.x < bullet.x < remote_player.x + 16) and \
                   (remote_player.y < bullet.y < remote_player.y + 16):
                    bullet.active = False
                    self.player.score += 1
                    remote_player.status = "morto"
                    

        self.mp_client.send_player_state(
            int(self.player.x), int(self.player.y),
            u=self.player.u, v=self.player.v,
            status=self.player.status,
            bullets=[{"x": b.x, "y": b.y, "dx": b.dx, "dy": b.dy} for b in self.bullets],
            score=self.player.score
        )

        # Atualiza os jogadores remotos e suas balas
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
                    remote_player.status = pdata.get("status", remote_player.status)
                self.remote_bullets[pid] = [Bullet(b["x"], b["y"], b["dx"], b["dy"]) for b in pdata.get("bullets", [])]

        # Verifica colisão das balas dos outros com o player local
        for bullets in self.remote_bullets.values():
            for bullet in bullets:
                if self.check_player_hit(bullet):
                    self.player.status = "morto"
                    # Após ser atingido, envie o estado atualizado para o servidor
                    self.mp_client.send_player_state(
                        int(self.player.x), int(self.player.y),
                        u=self.player.u, v=self.player.v,
                        status=self.player.status,
                        bullets=[{"x": b.x, "y": b.y, "dx": b.dx, "dy": b.dy} for b in self.bullets],
                        score=self.player.score
                    )
                    return
   
    def draw(self):
        if self.game_state == "inicio":
            pyxel.cls(pyxel.COLOR_NAVY)
            msg = "Press SPACE to start"
            pyxel.text((pyxel.width - len(msg)*4)//2, pyxel.height//2, msg, pyxel.COLOR_WHITE)
            return

        if len(self.mp_client.players) <= 1:
            pyxel.cls(pyxel.COLOR_NAVY)
            msg = "Waiting for players..."
            pyxel.text((pyxel.width - len(msg)*4)//2, pyxel.height//2 - 20, msg, pyxel.COLOR_WHITE)
            pyxel.text((pyxel.width - len("Como jogar:")*4)//2, pyxel.height//2 + 10, "Como jogar:", pyxel.COLOR_YELLOW)
            arrow_keys = "andar: W A S D"
            pyxel.text((pyxel.width - len(arrow_keys)*4)//2, pyxel.height//2 + 20, arrow_keys, pyxel.COLOR_WHITE)
            pyxel.text((pyxel.width - len("atirar: espaco")*4)//2, pyxel.height//2 + 30, "atirar: espaco", pyxel.COLOR_WHITE)
            return

        if self.player.status == "morto":
            pyxel.cls(pyxel.COLOR_NAVY)
            game_over_msg = "GAME OVER"
            pyxel.text((pyxel.width - len(game_over_msg)*4)//2, pyxel.height//2 - 20, game_over_msg, pyxel.COLOR_RED)
            msg = "Press ENTER to revive"
            pyxel.text((pyxel.width - len(msg)*4)//2, (pyxel.height//2) + 10, msg, pyxel.COLOR_WHITE)
            return

        cam_x = min(max(self.player.x - pyxel.width//2 + 8, 0), pyxel.tilemaps[0].width * 8 - pyxel.width)
        cam_y = min(max(self.player.y - pyxel.height//2 + 8, 0), pyxel.tilemaps[0].height * 8 - pyxel.height)
        pyxel.camera(cam_x, cam_y)
        pyxel.cls(1)
        map_width = pyxel.tilemaps[0].width * 8
        map_height = pyxel.tilemaps[0].height * 8
        pyxel.bltm(0, 0, 0, 0, 0, map_width, map_height, 0)
        pyxel.bltm(0, 0, 1, 0, 0, map_width, map_height, 0)

        for car in self.cars:
            car.draw()
        for _, remote_player in self.remote_players.items():
            if remote_player.status == "vivo":
                remote_player.draw()
        for bullets in self.remote_bullets.values():
            for bullet in bullets:
                bullet.draw()

        pyxel.camera()

        score_text = f"Score: {self.player.score}"
        padding = 4
        text_width = len(score_text)*4
        rect_x = 5 - padding//2
        rect_y = 5 - padding//2
        rect_width = text_width + padding
        rect_height = 10
        pyxel.rect(rect_x, rect_y, rect_width, rect_height, pyxel.COLOR_NAVY)
        pyxel.text(5, 5, score_text, pyxel.COLOR_WHITE)

App()