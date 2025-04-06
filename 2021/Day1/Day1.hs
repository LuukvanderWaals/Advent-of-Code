import System.IO
import Data.List

split :: String -> [String]
split [] = [""]
split (h:t) | h == '\n' = "":x:xs
                | otherwise = (h:x):xs
    where (x:xs) = split(t)


solve :: [Int] -> Int
solve (h1:t) | length t < 3 = 0
             | h1 < t !! 2 = solve t + 1
             | otherwise = solve t


main = do input <- readFile "Day1.txt"
          print(solve(map (read::String -> Int) (split input)))
