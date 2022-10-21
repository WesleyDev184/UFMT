TSIZE = 32
 --tamanho do tile
SCALE = 2
TSIZE = SCALE * 16

function love.load()
    love.graphics.setDefaultFilter('nearest', 'nearest')    
    tilemap = {
     

        {1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1},
        {1,0,3,0,1,0,5,0,1,0,1,3,1,0,5,0,3,0,3,1,0,3,0,1},
        {1,3,0,3,1,3,0,3,1,3,3,0,1,1,0,1,1,1,1,1,3,1,3,1},
        {1,1,5,0,1,1,3,1,2,0,1,3,2,0,3,1,0,3,0,1,0,1,0,1},
        {1,3,0,3,1,3,0,3,0,3,1,0,1,3,0,1,3,2,1,1,3,1,3,1},
        {1,0,1,1,2,0,1,1,1,0,1,3,2,1,3,1,0,3,0,3,0,1,0,1},
        {1,3,0,3,0,3,1,3,1,3,1,3,0,5,0,1,3,0,3,1,3,1,3,1},
        {1,0,5,0,3,0,3,0,1,0,3,0,1,0,3,1,1,1,0,1,1,1,0,1},
        {1,1,1,1,1,3,1,1,1,1,1,3,1,2,0,1,0,1,3,1,5,1,3,1},
        {1,1,2,1,1,0,1,1,2,1,1,0,3,0,3,1,3,2,0,1,0,1,0,1},
        {0,5,0,3,1,3,1,3,0,3,0,3,0,3,0,1,0,0,5,1,3,1,3,1},
        {1,0,3,0,2,0,2,0,3,0,1,1,1,1,3,2,3,1,0,1,0,1,0,4},
        {1,3,0,3,0,5,0,3,0,3,1,5,0,3,0,3,0,1,3,0,3,1,3,1},
        {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}



    }

    sprite={}
    sprite.wall = love.graphics.newImage("tile_0028.png")
    sprite.wall2 = love.graphics.newImage("tile_0029.png")
    sprite.floor = love.graphics.newImage("tile_0000.png")
    sprite.player = love.graphics.newImage("tile_0092.png")
    sprite.floor2 = love.graphics.newImage("tile_0024.png")
    sprite.comida = love.graphics.newImage("tile_0099.png")
    sprite.comida2 = love.graphics.newImage("tile_0097.png") 
    sprite.fant = love.graphics.newImage("tile_0108.png") 

    player= {x=3,y=2}

    sound = {}
    sound.point = love.audio.newSource('audio.wav', 'static')
    sound.move = love.audio.newSource('wow.wav', 'static')


end


function love .update(dt)

end


function love.draw()
    for i,row in ipairs(tilemap) do
        for j, col in ipairs(row) do
            
            if col == 1 then
                love.graphics.draw(sprite.wall,
                 j*TSIZE ,i * TSIZE ,0, -- coordenada x e y  do retangulo
                SCALE,SCALE) -- tamanho

            else if col == 2 then
                love.graphics.draw(sprite.wall2,
                 j*TSIZE ,i * TSIZE ,0, -- coordenada x e y  do retangulo
                SCALE,SCALE) -- tamanho
            
            else if col ==  0 or 6 or 5  then 
                love.graphics.draw(sprite.floor,
                j*TSIZE, i*TSIZE,0,
                SCALE,SCALE)

            end
        end
            
            if col == 3 then 
                love.graphics.draw(sprite.floor2,
                j*TSIZE, i*TSIZE,0,
                SCALE,SCALE)
                
            end
            if col == 4 then
                love.graphics.draw(sprite.comida,j*TSIZE, i*TSIZE,0,
                SCALE,SCALE)
            end

            if col == 5 then
                love.graphics.draw(sprite.comida2,j*TSIZE, i*TSIZE,0,
                SCALE,SCALE)
            end
            if col == 6 then
                love.graphics.draw(sprite.fant,j*TSIZE, i*TSIZE,0,
                SCALE,SCALE)
            end

            

                
            
            
        end
    end

end
        love.graphics.draw(sprite.player, player.x *TSIZE, player.y *TSIZE,0,SCALE,SCALE)
end
function love.keypressed(key)
    local x = player.x -- coluna onde se encontra o player
    local y = player.y -- linha onde se encontra o player

    if key == 'w' then
        y = y-1
        sound.move :play()
    end
    if key == 'a' then
        x = x - 1
        sound.move :play()
    end
    if key == 's' then
        y=y + 1
        sound.move :play()
    end
    if key == 'd' then
        x = x+1
        sound.move :play()
    end
    if tilemap[y][x] ~= 1 then -- não é parede
        player.x = x
        player.y = y
    end
    
    if tilemap[y][x] == 3 then
        sprite.player = love.graphics.newImage("tile_0089.png")
 
        
    end
    if tilemap[y][x] == 0 then
        sprite.player = love.graphics.newImage("tile_0092.png")
 
        
    end

    if tilemap[y][x] == 4 then
        sound.point :play()
        sprite.comida = love.graphics.newImage("tile_0064.png")
 
        
    end
    if tilemap[y][x] == 5 then
     sound.point :play()
       tilemap[y][x] = 6
 
        
    end
end