function love.load()
    bullet = love.graphics.newImage("bala.png")
    speed = 200 --20px p/s
    x = 0
    y = 100
    xscale = 1 --bala tamanho normal
end

function love.update(dt)
   x = x + speed * dt
end

function love.draw()
    love.graphics.setBackgroundColor(0/255, 138/255, 197/255)
    love.graphics.setColor(1, 1, 1)
    love.graphics.draw(bullet, x, y, 0, -0.5, 0.5)
    --Tree
    love.graphics.setColor(123/255, 63/255, 0/255)
    love.graphics.rectangle("fill", 60, 350, 30, 60)
    love.graphics.setColor(0/255, 232/255, 0/255)
    love.graphics.rectangle("fill", 40, 310, 70, 40)
    --Sun
    love.graphics.setColor(255/255, 232/255, 0/255)
    love.graphics.circle("fill", 700, 50, 40, 50, 100)
    --solo
    love.graphics.setColor(171/255, 143/255, 141/255)
    love.graphics.rectangle("fill", 0, 400, 800, 300)
    --Grama
    love.graphics.setColor(129/255, 186/255, 120/255)
    love.graphics.rectangle("fill", 0, 400, 800, 30)
end
