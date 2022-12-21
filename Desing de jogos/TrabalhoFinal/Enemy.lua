Enemy = Class{}
anim8 = require("lib/anim8")

function Enemy:init(world)
    self.world = world
    self.speed = 50
    self.spriteSheet = love.graphics.newImage('water_FREE_SpriteSheet_288x128.png')
    self.w = self.spriteSheet:getWidth() / 32
    self.h = self.spriteSheet:getHeight() / 15
    self.cw = self.w - 255
    self.ch  = self.h - 85
    f = anim8.newGrid(self.w, self.h,
                      self.spriteSheet:getWidth(),
                      self.spriteSheet:getHeight())
    self.animete = {}
    self.animete.idle = anim8.newAnimation(f('1-8', 1), 0.1)
    self.animete.run = anim8.newAnimation(f('1-8', 3), 0.1)
    self.body = world:newRectangleCollider(566, 100, self.cw, self.ch, {collision_class = 'Enemy'})
    self.body:setFixedRotation(true)
    self.direction = 1
end

function Enemy:update(dt)
    local x 
    local y
    
    x, y = self.body:getPosition()

    x = x + self.speed * dt

    self.curAnimation = self.animete.run
    self.body:setX(x)
    colliders = world:queryRectangleArea(x - self.cw/2, y + self.ch/2, self.cw, 3, 
                                        {'platform'}
                                    )

    if self.body:enter('enemyPlat') then
        self.direction = self.direction * -1
        self.speed = self.speed * -1
    end

    self.curAnimation:update(dt)
end

function Enemy:draw()
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