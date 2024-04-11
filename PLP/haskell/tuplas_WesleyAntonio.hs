import Char
type Pessoa = (String, Int, Float, Char)

pess :: Int->Pessoa
maiorIdade :: Int -> Int
maior :: Int -> Int -> Int
idade :: Pessoa -> Int
idadeMedia :: Int -> Float
somaIdade :: Int -> Float
mascSup25 :: Int -> Int
sexo :: Pessoa -> Char

-- Parte 2
triangulo :: (Float, Float, Float) -> (String, Float)

-- Parte 3
somaP :: Int -> Int

pess x
	|x==1 = ("Rosa", 27, 1.66,'F')
	|x==2 = ("João", 26, 1.85,'M')
	|x==3 = ("Maria", 67, 1.55,'F')
	|x==4 = ("Jose", 48, 1.78, 'M')
	|x==5 = ("Paulo", 24, 1.93, 'M')
	|x==6 = ("Clara", 38, 1.70,'F')
	|x==7 = ("Bob", 12, 1.45, 'M')
	|x==8 = ("Rosana", 31, 1.58,'F')
	|x==9 = ("Daniel", 75, 1.74, 'M')
	|x==10 = ("Jocileide", 21, 1.69,'F')
	|otherwise = ("Acabou!",0, 0.0, 'x')

maiorIdade x
  |x == 1 = 1
  |otherwise = maior (x) (maiorIdade (x-1))

maior x y
  |x1 >= y1 = x
  |otherwise = y
  where
    x1 = idade (pess x)
    y1 = idade (pess y)

idade (_,x,_,_) = x

idadeMedia x = (somaIdade x) / (fromIntegral x)

somaIdade x
	|x == 1 = fromIntegral (idade (pess x))
	|otherwise = (fromIntegral (idade (pess x))) + (somaIdade (x-1))

mascSup25 x
	|x == 1 = if (sexo (pess x) == 'M') && (idade (pess x) > 25) then 1 else 0
	|otherwise = if (sexo (pess x) == 'M') && (idade (pess x) > 25) then 1 + (mascSup25 (x-1)) else (mascSup25 (x-1))

sexo (_,_,_,x) = x

-- Parte 2
triangulo (a, b, c)
    | a + b <= c || a + c <= b || b + c <= a = ("Nao eh um triangulo", 0)
    | a == b && b == c = ("Equilatero", a + b + c)
    | a == b || b == c || a == c = ("Isosceles", a + b + c)
    | otherwise = ("Escaleno", a + b + c)

-- Parte 3
somaP n = somaPImpar n 0
    where
        somaPImpar :: Int -> Int -> Int
        somaPImpar 0 acc = acc
        somaPImpar x acc
            | odd x     = somaPImpar (x - 1) (acc + x)
            | otherwise = somaPImpar (x - 1) acc

-- Parte 4
serie :: (Float, Int) -> Float
serie (x,n) = calc (x,n) 0

calc::(Float,Int)->Float->Float
calc (x,n) y
	|n==1 = y + ((fromIntegral (n))/x)
	|odd n = calc (x, n-1) y+(fromIntegral (n))/x
	|even n = calc (x, n-1) y+(x/(fromIntegral (n)))