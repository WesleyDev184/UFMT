function love.load()

    height = love.graphics.getHeight()
    width = love.graphics.getWidth()
    
    sprite = {}
    sprite.bg = love.graphics.newImage("sprites/tile_01.png")
    sprite.bullet = love.graphics.newImage("sprites/tile_187.png")
    sprite.player = love.graphics.newImage("sprites/survivor1_machine.png")
    sprite.zoimbie = love.graphics.newImage("sprites/zoimbie1_hold.png")

    player = {}
    player.h = sprite.player:getHeight()/2
    player.w = sprite.player:getWidth()/2
    player.x = width / 2
    player.y = height / 2
    player.direction = 0 --girar a esquer ou direita
    player.angular_speed = 6
    player.speed = 180
    player.rotation = 0 --math.pi/2 -- radianos
    player.vector = {}

    bullets = {}
    bullets.speed = 500
    bullets.h = sprite.bullet:getHeight()/2
    bullets.w = sprite.bullet:getHeight()/2

    
end

function love.update(dt)

    player.direction = 0
    player.vector.x = 0
    player.vector.y = 0
    if love.keyboard.isDown('w') then
        player.vector.y = math.sin(player.rotation)
        player.vector.x = math.cos(player.rotation) 
    end
    if love.keyboard.isDown('d') then
        player.direction = 1
    end
    if love.keyboard.isDown('a') then
        player.direction = -1
    end
    player.rotation = player.rotation + player.direction * player.angular_speed * dt
    player.x = player.x + player.vector.x * player.speed * dt
    player.y = player.y + player.vector.y * player.speed * dt

    for i,b in ipairs(bullets) do 
        b.x = b.x + b.vector.x * bullets.speed * dt
        b.y = b.y + b.vector.y * bullets.speed * dt
    end

end

function love.draw()

    draw_bg()
    love.graphics.draw(sprite.player, 
        player.x, 
        player.y, 
        player.rotation,
        nil, nil,
        player.w,
        player.h
    )

    for i, b in ipairs(bullets) do
        love.graphics.draw(
            sprite.bullet,
            b.x, b.y, 0,
            nil, nil,
            bullets.h,
            bullets.w
        )
    end

end

function draw_bg()

    img_h = sprite.bg:getHeight()
    img_w = sprite.bg:getWidth()
    cols = math.ceil(width / img_w)
    rows = math.ceil(height / img_h)
    for row = 0, rows - 1 do
        for col = 0, cols - 1 do
            love.graphics.draw(sprite.bg, col * img_w, row * img_h)
        end
    end

end

function love.keypressed(key)
    if key == 'space' then
        local bullet = {}
        bullet.x = player.x
        bullet.y = player.y
        bullet.vector = {}
        bullet.vector.x = math.cos(player.rotation)
        bullet.vector.y = math.sin(player.rotation)
        table.insert(bullets, bullet)
    end
end