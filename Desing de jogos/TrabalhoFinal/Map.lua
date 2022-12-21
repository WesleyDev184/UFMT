Map = Class{}

function Map:init(world)
    self.world = world
    self.platforms = {}
    self.obstaculos = {}
    self.bandeiras = {}
    self.enemys = {}
    self.gameMap = sti('maps/level1.lua')
    self:CreatePlataforms()
    self:CreateObstaculo()
    self:CreateFinalPoit()
    self:CreateEnemyPlat()
end

function Map:update(dt)

end

function Map:draw()
    self.gameMap:drawLayer(self.gameMap.layers['Camada de Blocos 1'])
end

function Map:CreatePlataforms( ... )
    -- body
    local platform
    for _, obj in ipairs(self.gameMap.layers['Plataforma'].objects) do
        platform = self.world:newRectangleCollider(obj.x, obj.y, obj.width, obj.height,
                                        {collision_class = 'platform'})
        platform:setType('static')
        table.insert( self.platforms, platform)
    end
end

function Map:CreateObstaculo( ... )
    -- body
    local obstaculo
    for _, i in ipairs(self.gameMap.layers['Obstaculos'].objects) do
        obstaculo = self.world:newRectangleCollider(i.x, i.y, i.width, i.height,
                                        {collision_class = 'Obstaculo'})
        obstaculo:setType('static')
        table.insert( self.obstaculos, obstaculo)
    end
end

function Map:CreateFinalPoit( ... )
    -- body
    local bandeira
    for _, j in ipairs(self.gameMap.layers['Bandeira'].objects) do
        bandeira = self.world:newRectangleCollider(j.x, j.y, j.width, j.height,
                                        {collision_class = 'Bandeira'})
        bandeira:setType('static')
        table.insert( self.bandeiras, bandeira)
    end
end

function Map:CreateEnemyPlat( ... )
    -- body
    local enemy
    for _, l in ipairs(self.gameMap.layers['Inimigos'].objects) do
        enemy = self.world:newRectangleCollider(l.x, l.y, l.width, l.height,
                                        {collision_class = 'enemyPlat'})
        enemy:setType('static')
        table.insert( self.enemys, enemy)
    end
end