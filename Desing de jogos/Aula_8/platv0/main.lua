WINDOW_WIDTH = 854
WINDOW_HEIGHT = 480
--Dimensoes virtuais
WIDTH = 480
HEIGHT = 270

push =require("push")
require("Map") --Importa o mapa

mundo = Map()

function love.load( ... ) 
    -- body
    love.graphics.setDefaultFilter('nearest', 'nearest')
    push:setupScreen(WIDTH, HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT)
end

function love.update( dt )
    -- body
    mundo:update(dt)
end

function love.draw( ... )
    -- body
    push:start()

    love.graphics.translate(math.ceil( mundo.camX ), mundo.camY)
    love.graphics.clear(0,151/255,226/255)

    mundo:draw()

    push:finish()
end