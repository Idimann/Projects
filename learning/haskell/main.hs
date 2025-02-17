import qualified Data.Bool as Data

comparison :: (Int -> Int -> Bool) -> [Int] -> Bool

comparison fn [] = True
comparison fn [x] = True
comparison fn [x1, x2] = fn x1 x2
comparison fn [x1, x2, x3] = fn x1 x2 && fn x2 x3
comparison fn (x1:x2:x3:xs) = comparison fn [x1, x2] && comparison fn [x2, x3]

toString :: Bool -> String
toString True = "True"
toString False = "False"

main = putStr $ toString $ comparison (<) [1, 2, 2]
