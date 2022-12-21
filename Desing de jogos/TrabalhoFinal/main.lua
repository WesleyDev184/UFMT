WINDOW_WIDTH = 980
WINDOW_HEIGHT = 500
WIDTH = 640
HEIGHT = 360

push = require 'lib/push'
wf = require 'lib/windfield' -- física

sti = require 'lib/sti'
Class = require 'lib/class'
Camera = require 'lib/camera'

require 'Map' -- Nossa classe
require 'Player'
require 'Enemy'

function love.load()
    love.graphics.setDefaultFilter('nearest', 'nearest')
    push:setupScreen(WIDTH, HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT)
    world = wf.newWorld(0, 800, false)
    world:setQueryDebugDrawing(true) -- visualiza o campo de busca
    world:addCollisionClass('platform')
    world:addCollisionClass('Enemy')
    world:addCollisionClass('Obstaculo')
    world:addCollisionClass('Bandeira')
    world:addCollisionClass('enemyPlat')
    player = Player(world) -- inicialização (metodo init() em ação)
    map = Map(world)
    cam = Camera()
    enemy = Enemy(world)

    sound = {}
    sound.main = love.audio.newSource('mainSong.mp3', 'static')
    sound.jump = love.audio.newSource('fast-simple-chop-5-6270.mp3', 'static')

    smallFont = love.graphics.newFont('DebugFreeTrial-MVdYB.otf', 30)
    bigFont = love.graphics.newFont('DebugFreeTrial-MVdYB.otf', 50)

    imgs = {}
    imgs.bg = love.graphics.newImage('Test_1.png')
end

function love.update(dt)
    sound.main:setVolume(0.05)
    sound.main:play()
    world:update(dt)
    player:update(dt)
    enemy:update(dt)
end

function love.draw()
    if player.victory ~= true then
        
    push:start()
    cam:attach()
    love.graphics.draw(imgs.bg, 0, 0, 0, 1.5)
    -- world:draw()
    map:draw()
    player:draw()
    enemy:draw()

    if player.dead ~= true then
        cam:lookAt(player.body:getX(), HEIGHT-110)
    end
    cam:detach()
    love.graphics.setColor(254, 0, 0)
    love.graphics.setFont(bigFont)
    if player.dead == true then
        -- body
        love.graphics.printf('Game Over', 0, HEIGHT/3, WIDTH, 'center')
    end
    push:finish()
    else
        love.graphics.draw(imgs.bg, 0, 0, 0, 1.5)
        love.graphics.setColor(1, 1, 1)
        love.graphics.setFont(bigFont)
        love.graphics.printf('Fim da fase', 0, WINDOW_HEIGHT/3, WINDOW_WIDTH, 'center')
        love.graphics.setFont(smallFont)
        love.graphics.printf('você Chegou ao fim de sua aventura', 0, WINDOW_HEIGHT/2, WINDOW_WIDTH, 'center')

    end
end

function love.keypressed(key)
    if key == 'w' then
        sound.jump:setVolume(0.2)
        sound.jump:play()
        player:jump()
    end
end