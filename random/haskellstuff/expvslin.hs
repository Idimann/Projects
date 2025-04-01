isExp :: Float -> [Float] -> Bool
isExp factor [x, y] = factor == y / x
isExp factor (h : n : t) = isExp factor [h, n] && isExp factor (n : t)

expo :: [Float] -> Bool
expo [] = True
expo [_] = True
expo [_, _] = True
expo (h : n : t) = isExp (n / h) t

isLin :: Float -> [Float] -> Bool
isLin sum [x, y] = sum == y - x
isLin sum (h : n : t) = isLin sum [h, n] && isLin sum (n : t)

line :: [Float] -> Bool
line [_] = True
line [_, _] = True
line (h : n : t) = isLin (n - h) t

data Which = Expo | Line | Neither
which :: [Float] -> Which
which list
  | expo list = Expo
  | line list = Line
  | otherwise = Neither
