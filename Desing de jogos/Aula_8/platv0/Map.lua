Class = require("class")
Map = Class{}
EMPTY = -1
BRICK_ID = 19
BUSH_ID = 49    
CLOUD_ID = 54
CAM_SPEED = 200

function Map:init( ... )
    -- body
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

    middle = math.ceil( self.mapHeight/2 ) * self.mapWidth + 1
    for i=middle, #self.tileMap do
        self.tileMap[i] = BRICK_ID
    end

    self:SetTile(10,1, CLOUD_ID)
    self:SetTile(11,1, CLOUD_ID)
    self:SetTile(15,3, CLOUD_ID)

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
        self.camY = 0
    elseif love.keyboard.isDown('s') then
        -- body
        self.camY = 0
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