Fighter = Class{}

function Fighter:init(name, x, y, color)
    --Construtor
    self.name = name
    self.x = x
    self.y = y
    self.color = color

end

function Fighter:sayHello()
    love.graphics.print('oi, meu nome e ' .. self.name)
end

function Fighter:draw()
    love.graphics.setColor(self.color)
    love.graphics.rectangle('fill', self.x, self.y, 30, 30)
end