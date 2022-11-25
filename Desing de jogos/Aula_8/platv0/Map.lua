Class = require("class")
Map = Class{}
EMPTY = -1
BRICK_ID = 19
BUSH_ID = 49
CLOUD_ID = 54
ROCK_ID = 48
FLOWER_ID = 46
TREE1_ID = 24
TREE2_ID = 31
TREE3_ID = 38
water = 41

CAM_SPEED = 100

function Map:init( ... )
    -- body
    math.randomseed(os.time())
    self.tileset = love.graphics.newImage('nature-paltformer-tileset-16x16.png')
    self.tileWidth = 16
    self.tileHeight = 16
    self.mapWidth = 40
    self.mapHeight = 26
    self.tileMap = {}
    -- self.brick = love.graphics.newQuad(4 * self.tileWidth,
    --                                    2 * self.tileHeight,
    --                                    self.tileWidth,
    --                                    self.tileHeight,
    --                                    self.tileset:getWidth(),
    --                                    self.tileset:getHeight()
    --                                    )
    self.tileQuad = self:createQuads()
    self.camX = 0
    self.camY = 0
    for i=1,self.mapHeight * self.mapWidth do
        self.tileMap[i] = EMPTY
    end

    self:generateWorld()

end

function Map:draw( ... )
    -- body
    local tile_id
    for i=1,self.mapHeight do
        for j=1, self.mapWidth do
            tile_id = self:getTile(j, i)
            if tile_id ~= EMPTY then
                -- bodys
                love.graphics.draw(self.tileset,
                                   self.tileQuad[tile_id],
                                   self.tileWidth * (j - 1), 
                                   self.tileHeight * (i - 1)
                                   )
            end
        end
    end
end

function Map:createQuads( ... )
    -- body
    local tiles = {}
    local rows = self.tileset:getHeight()/self.tileHeight
    local cols = self.tileset:getWidth()/self.tileWidth

    for i=1,rows do
        for j=1,cols do
            tiles[(i-1) * cols + j] = love.graphics.newQuad((j-1) * self.tileWidth,
                                                            (i-1) * self.tileHeight,
                                                            self.tileWidth,
                                                            self.tileHeight,
                                                            self.tileset:getWidth(),
                                                            self.tileset:getHeight()
                                                            )
        end
    end
    return tiles
end

function Map:update( dt )
    -- body
    if love.keyboard.isDown('d') then
        self.camX =  math.max( self.camX - CAM_SPEED * dt,
         -(self.mapWidth * self.tileWidth - WIDTH))
    elseif love.keyboard.isDown('a') then
        -- body
        self.camX = math.min( self.camX + CAM_SPEED * dt, 0 ) 
    elseif love.keyboard.isDown('w') then
        -- body
        self.camY = math.min(self.camY + CAM_SPEED * dt, 0)
    elseif love.keyboard.isDown('s') then
        -- body
        self.camY = math.max(self.camY - CAM_SPEED * dt, -(self.tileHeight * self.mapHeight - HEIGHT))
    end
end

function Map:getTile( x,y )
    -- body
    return self.tileMap[(y-1) * self.mapWidth + x]
end

function Map:SetTile( x,y, tileid )
    -- body
    self.tileMap[(y-1) * self.mapWidth + x] = tileid
end

function Map:generateWorld()
    for x=1, self.mapWidth do -- percorre todo o ceu (acima do pavimento)
        -- COLOCO NUVEM?
        if math.random(1,10) == 1 then -- retorna um numero aleatorio de 1 a 10 
            y = math.random(1, math.ceil(self.mapHeight/2)-5) -- altura da nuvem ao acaso
            self:SetTile(x, y, CLOUD_ID)
        end

        if math.random(1,15)  == 1 then
            self:SetTile(x, self.mapHeight, water)
            
        else
            for y=math.ceil(self.mapHeight/2) + 1, self.mapHeight do         -- CONSTRUIR PAVIMENTO
                self:SetTile(x,y, BRICK_ID)
            end
        end

        -- ELEMENTOS EM CIMA DO PAVIMENTO--
        y = math.ceil(self.mapHeight/2)
        -- COLOCO FLOR?
        if math.random(1,20) == 1 then
            self:SetTile(x,y, FLOWER_ID)
        --COLOCO PEDRA?
        elseif math.random(1,20) == 1 then
            self:SetTile(x,y, ROCK_ID)
        --COLOCO ARBUSTO?
        elseif math.random(1,20) == 1 then
            self:SetTile(x,y, BUSH_ID)
        --COLOCO ARVORE?
        elseif math.random(1,20) == 1 then
            self:SetTile(x,y, TREE3_ID)
            self:SetTile(x,y-1, TREE2_ID)
            self:SetTile(x,y-2, TREE1_ID)
        end
        
    end 
end