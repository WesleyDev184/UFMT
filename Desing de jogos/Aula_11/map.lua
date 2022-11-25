    Map = class{}

function Map:init( world )
    -- body
    self.world = world
    self.gameMap = sti('maps/map_level1.lua')
end

function Map:update( dt )
    -- body
end

function Map:draw( ... )
    -- body
    self.gameMap:drawLayer(self.gameMap.layers['Camada de Blocos 1'])
end