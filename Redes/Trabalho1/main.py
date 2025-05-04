import random
import pyxel
from multplayer import MultiplayerClient

# -------------------------------
# Constantes e recursos visuais
# -------------------------------
HUMAN_IMAGES = [
    (368, 56, 16, 16),
    (368, 152, 16, 16),
    (368, 200, 16, 16),
]

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
        self.human_image = random.choice(HUMAN_IMAGES)  # Seleciona um sprite aleatório
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
            self.human_image[0] + self.u * 16,
            self.human_image[1] + self.v * 16,
            self.human_image[2],
            self.human_image[3],
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
        self.music_playing = False  # Variável de controle para a música

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

    def setup_music(self):
        # Canal 0 - Melodia principal (15s loop)
        pyxel.sounds[0].set(
            "g2 d2 f2 a2 a#2 r g2 d2 g2 d#2 r g2 f2 c3 d#2 r "
            "a2 f2 d#2 r g2 a#2 c3 d3 r g2 r f2 g2 r",
            "p",
            "66666666 66556655 65556666 66665566",
            "nfnfnnnn nnnnffff vnnnffvv ffffnnff",
            25,
        )

        # Canal 1 - Contramelodia
        pyxel.sounds[1].set(
            "r a1 r a#1 r d2 r f2 r g2 r f2 r e2 r f2 r "
            "r f2 r e2 r d2 r a#1 r f2 r d2 r",
            "s",
            "55443322 55667777 66554433 55443322",
            "vnnnvnnn vnnnvnnn vnnnvnnn vnnnvnnn",
            25,
        )

        # Canal 2 - Baixo
        pyxel.sounds[2].set(
            "c1 g0 c1 g0 a0 e0 a0 e0 f0 d0 f0 d0 c1 g0 c1 g0 "
            "d1 a0 d1 a0 e1 b0 e1 b0",
            "t",
            "7777",
            "n",
            25,
        )

        # Canal 3 - Percussão
        pyxel.sounds[3].set(
            "f0r r f0r r f0r f0r r r f0r f0r r r f0r r f0r r "
            "f0r f0r r r f0r f0r r r",
            "n",
            "6644",
            "f",
            25,
        )

        # Toca os canais 0, 1, 2 e 3 em loop
        pyxel.play(0, [0], loop=True)
        pyxel.play(1, [1], loop=True)
        pyxel.play(2, [2, 3], loop=True)
    
    def revive(self):
        spawn_x, spawn_y = random.choice(self.spawns)
        self.player = Player(spawn_x, spawn_y)
        self.bullets.clear()
        self.mp_client.send_player_state(
            int(self.player.x), int(self.player.y),
            u=self.player.u, v=self.player.v,
            status=self.player.status,
            bullets=[],
            score=self.player.score,
            human_image=self.player.human_image  # Envia o personagem escolhido
        )

    def check_player_hit(self, bullet):
        return (self.player.x < bullet.x < self.player.x + 16) and \
               (self.player.y < bullet.y < self.player.y + 16)

    def update(self):
        if self.game_state == "inicio":
            if pyxel.btnp(pyxel.KEY_SPACE):
                self.game_state = "jogando"
            return

        # Se o jogo já acabou, aguarda 10 segundos para reiniciar
        if self.game_state == "fim":
            if not hasattr(self, "end_timer"):
                self.end_timer = 300  # 10 segundos a 30 FPS
            else:
                self.end_timer -= 1
                if self.end_timer <= 0:
                    # Reset local player score
                    self.player.score = 0
                    # Reset score from all remote players
                    for remote_player in self.remote_players.values():
                        remote_player.score = 0
                        remote_player.status = "vivo"
                    self.game_state = "inicio"
                    del self.end_timer
            return

        if pyxel.btnp(pyxel.KEY_F5):
            import sys, subprocess
            subprocess.Popen(f'"{sys.executable}" {" ".join(sys.argv)}', shell=True)
            sys.exit()

        # Verifica se há mais de um jogador conectado e inicia a música
        if len(self.mp_client.players) > 1 and not self.music_playing:
            self.setup_music()
            self.music_playing = True

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
            self.shoot_cooldown = 90  # 3 segundos de cooldown

        for bullet in self.bullets:
            bullet.update(map_width, map_height)
        self.bullets = [b for b in self.bullets if b.active]

        # Verifica colisão da bala com jogadores remotos:
        for bullet in self.bullets:
            for pid, remote_player in self.remote_players.items():
                if remote_player.status == "vivo" and \
                   (remote_player.x < bullet.x < remote_player.x + 16) and \
                   (remote_player.y < bullet.y < remote_player.y + 16):
                    bullet.active = False
                    self.player.score += 1
                    remote_player.status = "morto"

        self.mp_client.send_player_state(
            int(self.player.x), int(self.player.y),
            u=self.player.u, v=self.player.v,
            status=self.player.status,
            bullets=[{"x": b.x, "y": b.y, "dx": b.dx, "dy": b.dy} for b in self.bullets],
            score=self.player.score,
            human_image=self.player.human_image  # Envia o personagem escolhido
        )

        # Atualiza os jogadores remotos e suas balas
        for pid, pdata in self.mp_client.players.items():
            if pid != self.mp_client.player_id:
                if pid not in self.remote_players:
                    # Cria um novo jogador remoto e força o uso do human_image enviado
                    player = Player(pdata["x"], pdata["y"])
                    player.human_image = tuple(pdata["human_image"]) if "human_image" in pdata else player.human_image
                    self.remote_players[pid] = player
                else:
                    remote_player = self.remote_players[pid]
                    remote_player.x = pdata["x"]
                    remote_player.y = pdata["y"]
                    remote_player.u = pdata.get("u", remote_player.u)
                    remote_player.v = pdata.get("v", remote_player.v)
                    remote_player.status = pdata.get("status", remote_player.status)
                    if "human_image" in pdata:
                        remote_player.human_image = tuple(pdata["human_image"])
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

        # Checar se local ou algum jogador remoto atingiu 5 pontos:
        if self.player.score >= 1:
            self.game_state = "fim"
            return

        for pid, pdata in self.mp_client.players.items():
            if pdata.get("score", 0) >= 1:
                self.game_state = "fim"
                return
   
    def draw(self):
        if self.game_state == "inicio":
            pyxel.cls(pyxel.COLOR_NAVY)
            msg = "Press SPACE to start"
            pyxel.text((pyxel.width - len(msg)*4)//2, pyxel.height//2, msg, pyxel.COLOR_WHITE)
            return

        if self.game_state == "fim":
            pyxel.cls(pyxel.COLOR_NAVY)
            title = "Fim de Jogo"
            pyxel.text((pyxel.width - len(title)*4)//2, 10, title, pyxel.COLOR_WHITE)
            y = 30
           
            # Lista os jogadores remotos:
            sorted_players = sorted(self.mp_client.players.items(), key=lambda item: item[1].get("score", 0), reverse=True)
            for pid, pdata in sorted_players:
                score = pdata.get("score", 0)
                pyxel.text(10, y, f"Player {pid}: {score}", pyxel.COLOR_WHITE)
                y += 10
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