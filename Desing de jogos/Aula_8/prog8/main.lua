wf = require 'lib/windfield'
math.randomseed(os.time())

function love.load()
    world = wf.newWorld(0,800, false) -- gravidade no eixo x e y 
    side = 64 -- tamanho do quadrado
    radius = 25 -- tamanho do circulo
    speed = 200
    sprite = love.graphics.newImage('face.png')

    world:setQueryDebugDrawing(true) -- area de busca 

    for i =1,4 do
        x = math.random(1,600) -- tamanho de x
        y = math.random(1,300) -- tamanho de y
        box = world:newRectangleCollider(x, y, side, side) -- desenha quadrado
        box:setRestitution(0.7) -- elasticidade do box
    end
    
    ground = world:newRectangleCollider(100,500, 800, 100) -- desenha retangulo/chao
    ground:setType('static')

    ground = world:newRectangleCollider(200,300, 300, 30) -- desenha retangulo/chao
    ground:setType('static')

    player = world:newRectangleCollider(x, y, side, side) -- desenha circulo

    player:setFixedRotation(true)
    player:setRestitution(0)
    
end

function love.update(dt)
    px = player:getX() -- posicao atual do eixo x de player
    if love.keyboard.isDown('a') then -- move pra direita
        px = px - speed * dt
    elseif love.keyboard.isDown('d') then -- move pra esquerda
        px = px + speed * dt
    end
    player:setX(px)
    world:update(dt) -- atualiza mundo
end

function love.keypressed(key)
    if key == 'p' then -- faz a bola pular ao pressionar p
        player:applyLinearImpulse(0, -2200)
    end

    if key == 'q' then
        colliders = world:queryCircleArea(player:getX(), player:getY(), 200) -- visualiza a area ao redor (colliders) do player
        for i, collider in ipairs(colliders) do
            if collider ~= player then
                if player:getX() <= collider:getX() then
                    collider:applyLinearImpulse(4000, 0)
                else
                    collider:applyLinearImpulse(-4000, 0)
                end
            end
        end
    end
end

function love.draw()
    world:draw() -- desenha mundo
    love.graphics.draw(sprite, player:getX()-side/2, player:getY()-side/2)

end
