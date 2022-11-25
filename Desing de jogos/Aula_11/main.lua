WINDOW_WIDTH = 980
WINDOW_HEIGHT = 500
WIDTH = 640
HEIGHT = 360

push = require("lib/push")
wf = require("lib/windfield") --fisica
class = require("lib/class")
sti = require("lib/sti")

require("Player")
require("Map")

function love.load( ... )
    -- body
    love.graphics.setDefaultFilter('nearest', 'nearest')
    push:setupScreen(WIDTH, HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT)
    world = wf.newWorld(0, 800, false)
    world:setQueryDebugDrawing(true)
    world:addCollisionClass('platform')

    ground = world:newRectangleCollider(10, 200, 600, 60)
    ground:setType('static')
    ground:setCollisionClass('platform')

    player = Player(world)
    map = Map(world)

end

function love.update( dt )
    -- body
    world:update(dt)
    player:update(dt)
end

function love.draw( ... )
    -- body
    push:start()
    world:draw()
    map:draw()
    player:draw()
    push:finish()
end


function love.keypressed( key )
    -- body
    if key == 'w' then
        player:jump()
    end
end