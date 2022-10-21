
Class = require("class")
require("Fighter")

-- Fighter("nome", "largura", "cor")
blanka = Fighter("Blanka", 200, 100, {0, 0.6, 0.0})
honda = Fighter("Honda", 400, 100, {0.2, 0.4, 0.7})

function love.draw()
    -- body
    blanka:draw()
    honda:draw()
end
