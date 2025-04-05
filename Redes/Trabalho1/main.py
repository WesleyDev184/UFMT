import pyxel

class Game:
    def __init__(self):
        pyxel.init(160, 120)
        pyxel.load("my_resource.pyxres")  # Carrega o arquivo de recursos com os sprites
        self.x = 0
        self.y = 0
        
        pyxel.run(self.update, self.draw)

    def update(self):
        if pyxel.btn(pyxel.KEY_RIGHT):
            self.x = (self.x + 1) % pyxel.width
        if pyxel.btn(pyxel.KEY_LEFT):
            self.x = (self.x - 1) % pyxel.width
        if pyxel.btn(pyxel.KEY_DOWN):
            self.y = (self.y + 1) % pyxel.height
        if pyxel.btn(pyxel.KEY_UP):
            self.y = (self.y - 1) % pyxel.height

    def draw(self):
        pyxel.cls(0)
        # Desenha o sprite:
        # pyxel.blt(x_destino, y_destino, banco de imagem, x_origem, y_origem, largura, altura, cor_chave para transparência)
        pyxel.blt(self.x, self.y, 0, 16, 0, 16, 16, 0)

Game()