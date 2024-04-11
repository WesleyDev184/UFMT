inc n = n + 1
soma x y = x + y
at b h = (b * h) / 2

par :: Int -> Bool
convFC :: Float -> Float

par x = if mod x 2 == 0 then True else False
convFC f = (f - 32) * 5/9