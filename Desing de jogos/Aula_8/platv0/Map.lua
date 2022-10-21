Class = require("class")
Map = Class{}
EMPTY = -1
BRICK_ID = 19

function Map:init( ... )
    -- body
    self.tileset = love.graphics.newImage('nature-paltformer-tileset-16x16.png')
    self.tileWidth = 16
    self.tileHeight = 16
    self.mapWidth = 40
    self.mapHeight = 26
    self.tileMap = {}
    self.brick = love.graphics.newQuad( 4 * self.tileWidth,
                                        2 * self.tileHeight,
                                        self.tileWidth,
                                        self.tileHeight,
                                        self.tileset:getWidth(),
                                        self.tileset:getHeight()
                                    )
    for i=1,self.mapHeight * self.mapWidth do
        self.tileMap[i] = EMPTY
    end
    self.tileMap[1] = BRICK_ID

end

function Map:draw( ... )
    -- body
    for i=1,self.mapHeight do
        for j=1, self.mapWidth do
            self.tileMap[(i-1) * self.mapWidth + j]
        end
    end
    love.graphics.draw( self.tileset,
                        self.brick,
                        0, 0
                    )

end