Player = Class{}
anim8 = require("lib/anim8")

function Player:init(world)
    self.world = world
    self.speed = 200
    self.spriteSheet = love.graphics.newImage('fire_FREE_SpriteSheet_288x128.png')
    self.w = self.spriteSheet:getWidth() / 28
    self.h = self.spriteSheet:getHeight() / 14
    self.cw = self.w - 255
    self.ch = self.h - 85
    f = anim8.newGrid(self.w, self.h,
                      self.spriteSheet:getWidth(),
                      self.spriteSheet:getHeight())
    self.animete = {}
    self.animete.idle = anim8.newAnimation(f('1-8', 1), 0.1)
    self.animete.run = anim8.newAnimation(f('1-8', 2), 0.1)
    self.animete.jump = anim8.newAnimation(f('1-8', 7), 0.08)
    self.curAnimation = self.animete.idle
    self.body = world:newRectangleCollider(10, 10, self.cw, self.ch)
    self.body:setFixedRotation(true)
    self.grounded = false
    self.direction = 1
    self.dead = false
    self.victory = false
end

function Player:update(dt)
    if self.dead then 
        return 
    end
    local x 
    local y
    x, y = self.body:getPosition()
    if love.keyboard.isDown('d') then
        x = x + self.speed * dt
        self.curAnimation = self.animete.run
        self.direction = 1
    elseif love.keyboard.isDown('a') then
        x = x - self.speed * dt
        self.curAnimation = self.animete.run
        self.direction = -1
    -- elseif love.keyboard.isDown('w') then
    --     self.curAnimation = self.animete.jump
    else 
        self.curAnimation = self.animete.idle
    end
    self.body:setX(x)
    colliders = world:queryRectangleArea(x - self.cw/2, y + self.ch/2, self.cw, 3, 
                                        {'platform'}
                                    )
    -- O player está apoiado sobre algum corpo? 
    if #colliders > 0 then
        self.grounded = true
    else
        self.grounded = false
    end

    
    if self.body:enter('Enemy') then
        self.body:destroy()
        self.dead = true 
    end

    if self.body:enter('Obstaculo') then
        self.body:destroy()
        self.dead = true 
    end

    if self.body:enter('Bandeira') then
        self.victory = true
    end

    self.curAnimation:update(dt)
end

function Player:jump()
    if self.dead then 
        return
    end
    -- O player pode fazer o salto?
    if self.grounded then
        self.body:applyLinearImpulse(0, -1150)
    end
end

function Player:draw()
    if self.dead then 
        return
    end
    self.curAnimation:draw(self.spriteSheet,
                           self.body:getX(),
                           self.body:getY(),
                           0, self.direction, 1,
                           self.w/2,
                           self.h/1.2
                        )
end