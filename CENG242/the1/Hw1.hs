module Hw1 where
data Cell = H | P | O | X deriving (Read,Show,Eq)
data Result = Fail | Caught (Int,Int) deriving (Read,Show,Eq)
data Direction = N | S | E | W deriving (Read,Show,Eq)

simulate_helper _ [] locations = Fail
simulate_helper environment (direction:rest) locations -- locations -> (H,P) where H->(), P->()
    | new_H == new_P = Caught new_H
    | otherwise = simulate_helper environment rest (new_H,new_P)
    where loc_H = fst locations
          loc_P = snd locations
          new_H = move loc_H (fst direction) environment
          new_P = move loc_P (snd direction) environment

simulate environment directions = 
    let locations = (location environment H,location environment P)
    in simulate_helper environment directions locations

move position direction multi_list
    | direction == W && 0 <= (fst position)-1 && moved_west /= X = ((fst position)-1,snd position)
    | direction == E && (fst position)+1 <= n && moved_east /= X = ((fst position)+1,snd position)
    | direction == N && 0 <= (snd position)-1 && moved_north /= X = (fst position,(snd position)-1)
    | direction == S && (snd position)+1 <= m && moved_south /= X = (fst position,(snd position)+1)
    | otherwise = (fst position, snd position)
    where moved_west= multi_list!!snd position!!((fst position)-1)
          moved_east= multi_list!!snd position!!((fst position)+1)
          moved_north= multi_list!!((snd position)-1)!!fst position
          moved_south= multi_list!!((snd position)+1)!!fst position
          n = (length (multi_list!!0)) - 1
          m = (length multi_list) - 1

pos_X_helper [] _ = []
pos_X_helper list agent = [ snd zp | zp <- zip list [0..] , agent == fst zp] 

pos_X (list:multi_list) agent 
    | position == [] = pos_X multi_list agent
    | otherwise = sum position
    where position = pos_X_helper list agent 

pos_Y multi_list agent = sum [ snd zp | zp <- zip multi_list [0..] , agent `elem` fst zp] 

location multi_list agent = (pos_X multi_list agent, pos_Y multi_list agent) 

