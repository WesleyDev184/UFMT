PATH = 'kenney_tinydungeon/Tiles/'
TSIZE = 16 -- tamanho do tile
WINDOW_WIDTH = 840
WINDOW_HEIGHT = 600
game_over = false
axe = false
sword = false
potion = false
-- Dimensões virtuais
WIDTH = 280
HEIGHT = 200

largeFont = love.graphics.newFont('stormfaze.ttf', 60)
Font = love.graphics.newFont('stormfaze.ttf', 20)

push = require 'push'
function love.load()
    love.graphics.setDefaultFilter('nearest', 'nearest')
    push:setupScreen(WIDTH, HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT)
    tilemap = {
        {1,1,1,1,1,1,1,1,1,1,1,1,0,0},
        {1,0,0,0,0,0,6,0,0,0,0,1,0,0},
        {1,0,1,1,1,0,1,1,1,1,0,1,0,0},
        {1,0,1,9,0,3,0,0,0,0,7,1,0,0},
        {1,0,1,1,1,0,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,1,0,0,0,0,4,0,0},
        {1,0,0,0,0,0,1,1,1,0,0,0,0,0},
        {1,0,0,0,5,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1}
            }
    sprite = {}
    sprite.wall = love.graphics.newImage(PATH .."tile_0014.png")
    sprite.floor = love.graphics.newImage(PATH .."tile_0049.png")
    sprite.player = love.graphics.newImage(PATH .."tile_0097.png")
    sprite.monster = love.graphics.newImage(PATH .."tile_0109.png")
    sprite.axe = love.graphics.newImage(PATH .."tile_0118.png")
    sprite.sword = love.graphics.newImage(PATH .."tile_0106.png")
    sprite.potion = love.graphics.newImage(PATH .."tile_0113.png")

    axe_pos = {x= 7, y=2}
    sword_pos = {x= 5, y=8}
    postion_pos = {x=12, y = 6}
    monster = {x=6, y=4}

    player = {}
    player.x = 3
    player.y = 2
    time_limit = 1 --segundos
    timer = time_limit
    limit_mob = 1

end

function love.update(dt)
    timer = timer - dt
    if timer <= 0 then
        monster.x = monster.x + limit_mob
        timer = time_limit
    end
    mod_direction()
    if axe == true then
    sprite.axe = sprite.floor
    end
    if sword == true then
        sprite.sword = sprite.floor
    end
    if potion == true then
        sprite.potion = sprite.floor
    end
end

function love.draw()
    push:start()
    for i, row in ipairs(tilemap) do
        for j, col in ipairs(row) do
            if col == 1 then
                love.graphics.draw( sprite.wall, 
                                    j * TSIZE, i * TSIZE)
            elseif col == 0 or col == 3 or col == 6 or col == 5 or col == 4 or col == 9 or col == 7 then
                love.graphics.draw( sprite.floor, 
                                    j * TSIZE, i * TSIZE)
                love.graphics.draw( sprite.monster, 
                                    monster.x * TSIZE, monster.y * TSIZE)
                love.graphics.draw( sprite.axe, 
                                    axe_pos.x * TSIZE, axe_pos.y * TSIZE)
                love.graphics.draw( sprite.sword, 
                                    sword_pos.x * TSIZE, sword_pos.y * TSIZE)
                love.graphics.draw( sprite.potion, 
                                    postion_pos.x * TSIZE, postion_pos.y * TSIZE)
            end
        end
    end
    if game_over == false then
        -- body
        love.graphics.draw( sprite.player, 
                        player.x * TSIZE, player.y * TSIZE)
    elseif game_over == true then
    love.graphics.draw( sprite.player, 
                        8 * TSIZE, 5 * TSIZE)
    end
    
    push:finish()
    love.graphics.setFont(Font)
    love.graphics.printf('Inventario', 0, 10, WINDOW_WIDTH, 'center')
    
    if axe == true then
        -- body
        love.graphics.draw( sprite.get_axe, 50 , 10 )
    end
    if sword == true then
        -- body
        love.graphics.draw( sprite.get_sword, 70 , 10 )
    end
    if potion == true then
        -- body
        love.graphics.draw( sprite.get_potion, 90 , 10 )
    end
    love.graphics.setFont(largeFont)
    if game_over == true then
        love.graphics.printf('GAME OVER', 0, WINDOW_HEIGHT/2, WINDOW_WIDTH, 'center')
    end
end

function mod_direction( ... )
    -- body
    local x = monster.x
    local y = monster.y 
    if tilemap[y][x] == 9 then
        limit_mob = 1
    end
    if tilemap[y][x] == 7 then
        limit_mob = -1
    end
end

function love.keypressed(key)
    local x = player.x -- coluna onde se encontra o player
    local y = player.y -- linha onde se encontra o player

    if key == 'w' then
        y = y - 1
    end
    if key == 'a' then
        x = x - 1
    end
    if key == 's' then
        y = y + 1
    end
    if key == 'd' then
        x = x + 1
    end
    if tilemap[y][x] ~= 1 then 
        --não é parede
        player.x = x
        player.y = y
    end

    if tilemap[y][x] == 3 then
    sprite.player = love.graphics.newImage(PATH .."tile_0108.png")
    game_over = true
    end

    if tilemap[y][x] == 6 then
        sprite.get_axe = love.graphics.newImage(PATH .."tile_0118.png")
        axe = true
    end
    if tilemap[y][x] == 5 then
        sprite.get_sword = love.graphics.newImage(PATH .."tile_0106.png")
        sword = true
    end
    if tilemap[y][x] == 4 then
        sprite.get_potion = love.graphics.newImage(PATH .."tile_0113.png")
        potion = true
    end
end

