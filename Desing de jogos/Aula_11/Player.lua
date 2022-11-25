Player = class{}

function Player:init( world )
    -- body
    self.world = world
    self.speed = 200
    self.w = 20
    self.h = 20
    self.body = world:newRectangleCollider(10, 10, self.w, self.h)
    self.body:setFixedRotation(true)
    self.grounded = false
end

function Player:update( dt )
    -- body
    local x
    local y 
    x,y = self.body:getPosition()

    if love.keyboard.isDown('d') then
        x = x + self.speed * dt
    elseif love.keyboard.isDown('a') then
        x = x - self.speed * dt
    end
    self.body:setX(x)
    colliders = world:queryRectangleArea(x - self.w/2, y + self.h/2, self.w, 3,
                                            {'platform'})

    if #colliders > 0 then
        -- body
        self.grounded = true
    else
        self.grounded = false
    end
end

function Player:jump( ... )
    -- body
    if self.grounded then
        self.body:applyLinearImpulse(0, -200)
    end
end

function Player:draw( ... )
    -- body
end