function love.load()
    math.randomseed(os.time())
    heigth = love.graphics.getHeight()
    width = love.graphics.getWidth()

    racket1 = {}
    racket1.w = 20
    racket1.h = 80
    racket1.x = 10
    racket1.y = heigth/2 - racket1.h/2
    racket1.dy = 0
    racket1.score = 0

    racket2 = {}
    racket2.w = 20
    racket2.h = 80
    racket2.x = width - 30
    racket2.y = heigth/2 - racket2.h/2
    racket2.dy = 0
    racket2.score = 0

    ball = {}
    ball.service_direction = 1
    ball.w = 20
    ball.h = 20
    ball.x = width/2 - ball.w/2
    ball.y = heigth/2 - ball.h/2
    ball.dx = 0
    ball.dy = 0

    smallFont = love.graphics.newFont('stormfaze.ttf', 30)
    bigFont = love.graphics.newFont('stormfaze.ttf', 50)

    sound = {}
    sound.hit_screen = love.audio.newSource('Hit_hurt 12.wav', 'static')
    sound.point = love.audio.newSource('Hit_hurt 3.wav', 'static')

    state = 'start'

end

function love.update(dt)
    if collides(ball,  racket1) then
        ball.dx = ball.dx * -1 * 1.1
        ball.x = racket1.x + racket1.w
        ball.dy = math.random(-300, 300)
        sound.point:play()
    end

    if ball.x < 0 then
        centralized(ball)
        racket2.score = racket2.score + 1
        ball.service_direction = 1
        if racket2.score == 3 then
            state = 'start'
        else
            state = 'serve'
        end
    end

    if ball.x + ball.w > width then
        centralized(ball)
        racket1.score = racket1.score + 1
        ball.service_direction = -1
        if racket1.score == 3 then
            state = 'start'
        else
            state = 'serve'
        end    
    end

    if ball.y < 0 then
        ball.y = 0
        ball.dy = ball.dy * -1
        sound.hit_screen:play()
    end

    if ball.y + ball.h > heigth then
        ball.y = heigth - ball.h
        ball.dy = ball.dy * -1
        sound.hit_screen:play()
    end

    if love.keyboard.isDown('w') then
        racket1.dy = -500
    elseif love.keyboard.isDown('s') then
        racket1.dy = 500
    else 
        racket1.dy = 0
    end

    if love.keyboard.isDown('up') then
        racket2.dy = -500
    elseif love.keyboard.isDown('down') then
        racket2.dy = 500
    else 
        racket2.dy = 0
    end

    if collides(ball,  racket2) then
        ball.dx = ball.dx * -1 * 1.1
        ball.x = racket2.x - ball.w
        sound.point:play()
    end

    ball.x = ball.x + ball.dx * dt   --dt faz a velocidade depender do tempo
    ball.y = ball.y + ball.dy * dt
    racket1.y = racket1.y + racket1.dy * dt
    racket2.y = racket2.y + racket2.dy * dt
    confinesRacket(racket1)
    confinesRacket(racket2)

end

function love.draw()
    love.graphics.setColor(1,1,1)
    love.graphics.setFont(smallFont)
    if state == 'start' then 
        love.graphics.printf('Precione Enter para jogar', 0, heigth/3, width, 'center')
    elseif state == 'serve' then
        love.graphics.printf('Precione Spaco para sacar', 0, heigth/3, width, 'center')
    end
    love.graphics.setFont(bigFont)
    if state ~= 'start' then
        love.graphics.printf(racket1.score, 200, heigth/2, width, 'left')
        love.graphics.printf(racket2.score, -200, heigth/2, width, 'right')
    end
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

function confinesRacket(racket)
    if racket.y <= 0 then
        racket.y = 0
    end
    
    if racket.y + racket.h >= heigth then
        racket.y = heigth - racket.h
    end
end

function centralized(ball)
    ball.x = width/2 - ball.w/2
    ball.y = heigth/2 - ball.h/2
    ball.dy = 0
    ball.dx = 0
end

function  love.keypressed(key)
    if state == 'start' and key == 'return' then
        ball.dx = -500
        state = 'play'
        racket1.score = 0
        racket2.score = 0
    end

    if state == 'serve' and key == 'space' then
        ball.dx = ball.service_direction * 500
        ball.dy = math.random(-300, 300)
        state = 'play'
    end
end