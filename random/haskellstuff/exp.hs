fn :: Float -> Float -> (Float -> Float)
fn base growth x = base * growth ** x

loop b g = do
  line <- getLine
  print $ fn b g (read line :: Float)
  loop b g

main = do
  base <- getLine
  growth <- getLine
  let b = read base :: Float
  let g = read growth :: Float
  loop b g
