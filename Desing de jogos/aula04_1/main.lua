ANGULAR_SPEED = 6
PLAYER_SPEED = 200
BULLET_SPEED = 500
MONSTER_SPEED = 80

function love.load()
    
    sound = {}
    sound.disparo = love.audio.newSource("disparo.wav", "static")
    sound.acerto = love.audio.newSource("acerto.wav", "static")
    sound.gameover = love.audio.newSource("gameover.wav", "static")

    acabou = 0

    ataque_especial = 0
    time_ataque_especial = 1

    math.randomseed(os.time())

    sprite = {}
    sprite.bg = love.graphics.newImage("sprites/grama.png")
    sprite.bg_h = sprite.bg:getHeight()
    sprite.bg_w = sprite.bg:getWidth()

    sprite.bullet = love.graphics.newImage("sprites/bala.png")
    sprite.bullet_h = sprite.bullet:getHeight()
    sprite.bullet_w = sprite.bullet:getWidth()

    sprite.player = love.graphics.newImage("sprites/prota.png")
    sprite.player_h = sprite.player:getHeight()
    sprite.player_w = sprite.player:getWidth()

    sprite.monster = love.graphics.newImage("sprites/enimy.png")
    sprite.monster_h = sprite.monster:getHeight()
    sprite.monster_w = sprite.monster:getWidth()

    height = love.graphics.getHeight()
    width = love.graphics.getWidth()

    player = {}
    player.x = width / 2 - sprite.player_w / 2
    player.y = height / 2 - sprite.player_h / 2
    player.direction = 0 --gira para a esquerda ou direita
    --player.rotation = math.pi/2 -- radianos
    player.rotation = 0
    player.vector = {}
    player.vector.x = 0
    player.vector.y = 0
    player.p = 0

    --lista de balas
    bullets = {}

    --lista de inimigos
    monsters = {}

    time_limit = 3 -- segundos
    timer = time_limit
    timer2 = 1
    timer3 = time_limit*3

end

function love.update(dt)
    
    --verifica se o jogo acabou
    if acabou == 0 then

        --temporizador
        timer = timer - dt
        if timer <= 0 then
            --esgotou o tempo
            create_monster()
            timer = time_limit --reset
            if time_limit > 0.5 then
                time_limit = time_limit - 0.2
            end
        end
        
        --movimento do player
        player.direction = 0
        player.vector.x = 0
        player.vector.y = 0

        if love.keyboard.isDown('d') then
            --player.vector.y = - math.cos(player.rotation)
            --player.vector.x = - math.sin(player.rotation)
            player.vector.x = player.vector.x + 1
        end
        if love.keyboard.isDown('a') then
            --player.vector.y = math.cos(player.rotation)
            --player.vector.x = math.sin(player.rotation)
            player.vector.x = player.vector.x - 1
        end
        if love.keyboard.isDown('w') then
            --player.vector.y = math.sin(player.rotation)
            --player.vector.x = math.cos(player.rotation)
            player.vector.y = player.vector.y - 1
        end
        if love.keyboard.isDown('s') then
            --player.vector.y = - math.sin(player.rotation)
            --player.vector.x = - math.cos(player.rotation)
            player.vector.y = player.vector.y + 1
        end

        if ataque_especial == 0 then
            player.rotation = player_mouse_angle()
        end

        player.x = player.x + player.vector.x * PLAYER_SPEED * dt
        player.y = player.y + player.vector.y * PLAYER_SPEED * dt

        --remover balas fora do viewport
        for i = #bullets, 1, -1 do
            local b = bullets[i]
            if b.x < 0 or b.x > width or b.y < 0 or b.y > height then
                table.remove(bullets, i)
            end
            --verificar se a bala atinjio o monstro
            for j=#monsters, 1, -1 do
                local m = monsters[j]
                if collides(b, m, 25) then
                    table.remove(monsters, j)
                    table.remove(bullets, i)
                    sound.acerto:play() --toca som
                    player.p = player.p + 1
                end
            end
        end

        --atualizar a posicao das balas
        for i, b in ipairs(bullets) do
            b.x = b.x + b.vector.x * BULLET_SPEED * dt
            b.y = b.y + b.vector.y * BULLET_SPEED * dt
        end

        --atualizar a posicao dos monstros
        for i, b in ipairs(monsters) do
            b.x = b.x + math.cos(b.rotation) * MONSTER_SPEED * dt
            b.y = b.y + math.sin(b.rotation) * MONSTER_SPEED * dt
            b.rotation = player_monster_angle(b)
        end

        --temporizador de especial
        timer3 = timer3 - dt
        if timer3 <= 0 then
            time_ataque_especial = 1
        end

        --ataque especial
        if ataque_especial == 1 then
            timer2 = timer2 - dt
            player.rotation = player.rotation + 0.2
            local bullet = {}
            bullet.x = player.x
            bullet.y = player.y
            bullet.vector = {}
            bullet.vector.x = math.cos(player.rotation)
            bullet.vector.y = math.sin(player.rotation)
            sound.disparo:play() --toca som
            table.insert(bullets, bullet) -- insere a bala na listade balas
        
            if timer2 <= 0 then
                timer2 = 1
                timer3 = 9
                time_ataque_especial = 0
                ataque_especial = 0
            end
        end
        
        --encerrar o jogo
        for j = #monsters, 1, -1 do
            local m = monsters[j]
            if collides(player, m, 25) then
                acabou = 1
                sound.gameover:play() --toca som
            end
        end
    end


end

function love.draw()
    --desenha o backgrownd
    draw_bg()

    --desenha o player
    love.graphics.draw(sprite.player, player.x, player.y, player.rotation, nil, nil, sprite.player_w/3, sprite.player_h/2)

    --desenha as balas
    for i, b in ipairs(bullets) do
        love.graphics.draw(sprite.bullet, b.x, b.y, nil, nil, nil, sprite.bullet_w/2, sprite.bullet_h/2)
    end

    --desenha os monstros
    for i, b in ipairs(monsters) do
        love.graphics.draw(sprite.monster, b.x, b.y, b.rotation, nil, nil, sprite.monster_w/3, sprite.monster_h/3)
    end

    --numero de pontos
    font = love.graphics.newFont(20)
    love.graphics.setFont(font)
    love.graphics.printf("Pontos:" .. player.p, 0, 15, love.graphics.getWidth(), "center")

    --numero de pontos
    if time_ataque_especial == 1 then
        love.graphics.printf("Pressione T!", 15, 15, love.graphics.getWidth())
    end

    --game over
    if acabou == 1 then
        font = love.graphics.newFont(65)
        love.graphics.setColor(255, 000, 000)
        love.graphics.setFont(font)
        love.graphics.printf("GAME OVER", 0, 180, love.graphics.getWidth(), "center")
    end

end

function draw_bg()
    cols = math.ceil(width / sprite.bg_w)
    rows = math.ceil(height / sprite.bg_h)

    for row=0, rows-1 do
        for col=0, cols-1 do
            love.graphics.draw(sprite.bg, col * sprite.bg_w, row * sprite.bg_h)
        end
    end
end

function love.keypressed(key)

    if love.keyboard.isDown('t') and time_ataque_especial == 1 then
        ataque_especial = 1
    end

end

function love.mousepressed(x, y, button, istouch, presses)
    if button == 1 then
        local bullet = {}
        bullet.x = player.x
        bullet.y = player.y
        bullet.vector = {}
        bullet.vector.x = math.cos(player.rotation)
        bullet.vector.y = math.sin(player.rotation)
        sound.disparo:play() --toca som
        table.insert(bullets, bullet) -- insere a bala na listade balas
    end
end

function create_monster()
    local monster = {}

    l = math.random(1, 4)

    if l == 1 then
        monster.x = -30
        monster.y = math.random(0, height)
    end
    if l == 2 then
        monster.x = math.random(0, width)
        monster.y = -30
    end
    if l == 3 then
        monster.x = width + 30
        monster.y = math.random(0, height)
    end
    if l == 4 then
        monster.x = math.random(0, width)
        monster.y = height + 30
    end

   
    monster.rotation = player_monster_angle(monster)
    table.insert(monsters, monster)

end

function collides(a, b, min)
    --distancia euclidiana entre 2 pontos
    h = math.sqrt((a.x - b.x)^2 + (a.y - b.y)^2)
    if h < min then
        return true
    end
    return false
end

function player_monster_angle(monster)
    --angulo entre player e monstro
    return math.atan2(player.y - monster.y, player.x - monster.x)
end

function player_mouse_angle()
    --angulo entre player e monstro
    return math.atan2(love.mouse.getY() - player.y, love.mouse.getX() - player.x)
end