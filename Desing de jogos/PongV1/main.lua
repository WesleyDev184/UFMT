function love.load()
    math.randomseed(os.time())
    heigth = love.graphics.getHeight()
    width = love.graphics.getWidth()

    racket1 = {}
    racket1.w = 20
    racket1.h = 80
    racket1.x = 10
    racket1.y = heigth/2 - racket1.h/2

    racket2 = {}
    racket2.w = 20
    racket2.h = heigth --80
    racket2.x = width - 21
    racket2.y = 0 --heigth/2 - racket2.h/2

    ball = {}
    ball.w = 20
    ball.h = 20
    ball.x = width/2 - ball.w/2
    ball.y = heigth/2 - ball.h/2
    ball.dx = -400
    ball.dy = 0
end

function love.update(dt)
    if collides(ball,  racket1) then
        ball.dx = ball.dx * -1
        ball.dy = math.random(-300, 300)
    end
    if collides(ball,  racket2) then
        ball.dx = ball.dx * -1
    end
    ball.x = ball.x + ball.dx * dt   --dt faz a velocidade depender do tempo
    ball.y = ball.y + ball.dy * dt
end

function love.draw()
    love.graphics.setColor(1,1,1)
    love.graphics.rectangle("line", racket1.x, racket1.y, racket1.w, racket1.h)
    love.graphics.rectangle("line", racket2.x, racket2.y, racket2.w, racket2.h)
    love.graphics.rectangle("line", ball.x, ball.y, ball.w, ball.h)
end

function collides(ball, racket)
    -- Algoritimo AABB
    --bola abixo ou acima da racket
    if ball.y > racket.y + racket.h or ball.y + ball.h < racket.y then
        return false
    end
    --bola a esquerda ou direita da racket
    if ball.x > racket.x + racket.w or ball.x + ball.w < racket.x then
        return false
    end
    return true
end
