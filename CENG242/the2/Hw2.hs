module Hw2 where
import Data.List 
data Level = Newbie | Intermediate | Expert deriving (Enum, Eq, Ord, Show, Read)
data Hunter = Hunter {hID::Int, hlevel::Level, hEnergy::Int, hNumberOfCatches::Int, hActions::[Direction]} deriving (Eq, Show, Read)
data Prey = Prey {pID::Int, pEnergy::Int, pActions::[Direction]} deriving (Eq, Show, Read)
data Cell = O | X | H Hunter | P Prey | T deriving (Eq, Show, Read)
data Direction = N | S | E | W deriving (Eq, Show, Read)
type Coordinate = (Int, Int)
-- DO NOT CHANGE THE DEFINITIONS ABOVE. --
instance Ord Hunter where
    (Hunter hID1 hLevel1 hEnergy1 hNumberOfCatches1 _) `compare` (Hunter hID2 hLevel2 hEnergy2 hNumberOfCatches2 _) | hLevel1 /= hLevel2 = compare hLevel1 hLevel2 | hEnergy1 /= hEnergy2 = compare hEnergy1 hEnergy2 | hNumberOfCatches1 /= hNumberOfCatches2 = compare hNumberOfCatches1 hNumberOfCatches2 | otherwise = compare hID2 hID1
instance Ord Prey where
    (Prey pID1 pEnergy1 _) `compare` (Prey pID2 pEnergy2 _) | pEnergy1 /= pEnergy2 = compare pEnergy1 pEnergy2 | otherwise = compare pID2 pID1

extractHunter (H rest) = rest
extractPrey (P rest) = rest
isHunter (H rest) = True 
isHunter _ = False
isPrey (P rest) = True 
isPrey _ = False

coor_X_helper [] _ = []
coor_X_helper list agent = [ snd zp | zp <- zip list [0..] , agent == fst zp] 
coor_X (list:world) agent = if pos==[] then coor_X world agent else sum pos
    where pos = coor_X_helper list agent 
coor_Y world agent = sum [ snd zp | zp <- zip world [0..] , agent `elem` fst zp] 
location world agent = (coor_X world agent, coor_Y world agent) 
myHunters world = [ (extractHunter element,location world element) | element <- concat world, isHunter(element)==True]
myPreys world = [ (extractPrey element,location world element) | element <- concat world, isPrey(element)==True]

move_location coordinates direction
    | direction == N = (fst coordinates,(snd coordinates)-1)
    | direction == S = (fst coordinates,(snd coordinates)+1)
    | direction == W = ((fst coordinates)-1,snd coordinates)
    | direction == E = ((fst coordinates)+1,snd coordinates)
moveHunter world agent
    | hActions (fst agent) == [] = agent
    | hEnergy (fst agent) < 10 = (Hunter (hID (fst agent)) (hlevel (fst agent)) ((hEnergy (fst agent))+1) (hNumberOfCatches (fst agent)) (drop 1 (hActions (fst agent))),snd agent)
    | 0 <= fst new_location && fst new_location < n && 0 <= snd new_location && snd new_location < m && newCell /= X = (Hunter (hID (fst agent)) (hlevel (fst agent)) ((hEnergy (fst agent))-1) (hNumberOfCatches (fst agent)) (drop 1 (hActions (fst agent))),new_location)
    | otherwise = (Hunter (hID (fst agent)) (hlevel (fst agent)) ((hEnergy (fst agent))-1) (hNumberOfCatches (fst agent)) (drop 1 (hActions (fst agent))),snd agent)
    where n = length (world!!0)
          m = length world
          newCell = world!!(snd new_location)!!(fst new_location)
          new_location = move_location (snd agent) ((hActions (fst agent))!!0)
movePrey world agent
    | pActions (fst agent) ==[] = agent
    | pEnergy (fst agent) < 10 = (Prey (pID (fst agent)) ((pEnergy (fst agent))+1) (drop 1 (pActions (fst agent))),snd agent)
    | 0 <= fst new_location && fst new_location < n && 0 <= snd new_location && snd new_location < m && newCell /= X = (Prey (pID (fst agent)) ((pEnergy (fst agent))-1) (drop 1 (pActions (fst agent))),new_location)
    | otherwise = (Prey (pID (fst agent)) ((pEnergy (fst agent))-1) (drop 1 (pActions (fst agent))),snd agent)
    where n = length (world!!0)
          m = length world
          newCell = world!!(snd new_location)!!(fst new_location)
          new_location = move_location (snd agent) ((pActions (fst agent))!!0)

decreasePreyEnergy10 prey = (Prey (pID (fst prey)) (if 10<(pEnergy (fst prey)) then (pEnergy (fst prey))-10 else 0) (pActions (fst prey)),snd prey)
   
updatePreys world h preys = survived_preys
    where preys_locations = [snd p | p <- preys]
          caughtPreys = elemIndices (snd h) preys_locations
          survived_preys 
              | (length caughtPreys)==0 = preys
              | (length caughtPreys)==1 = [fst zp | zp <- zip preys [0..], snd zp /= caughtPreys!!0 ]
              | (length caughtPreys)>=2 = [fst zp | zp <- zip preys [0..], snd zp /= caughtPreys!!0, snd zp /= caughtPreys!!1]
          
updateBoth world [] preys accumulated_new_hunters = (accumulated_new_hunters,preys)
updateBoth world (h:rest) preys accumulated_new_hunters = updateBoth world rest updated_preys (accumulated_new_hunters++[new_hunter]) 
    where updated_preys = updatePreys world h preys 
          new_hunter 
              | (length preys)-(length updated_preys)==0 = h
              | (length preys)-(length updated_preys)==1 = (Hunter (hID (fst h)) (hlevel (fst h)) (if (hEnergy (fst h))<80 then (hEnergy (fst h))+20 else 100) ((hNumberOfCatches (fst h))+1) (hActions (fst h)),snd h)
              | (length preys)-(length updated_preys)==2 = (Hunter (hID (fst h)) (hlevel (fst h)) (if (hEnergy (fst h))<60 then (hEnergy (fst h))+40 else 100) ((hNumberOfCatches (fst h))+2) (hActions (fst h)),snd h)
          
simulate_helper world hunters preys 
    | hActions (fst (hunters!!0)) == [] = (reverse (sortBy (\(a,_) (b,_) -> compare a b) hunters),sortBy (\(a,_) (b,_) -> compare a b) preys)
    | preys == [] = (reverse (sortBy (\(a,_) (b,_) -> compare a b) hunters),[])
    | otherwise = simulate_helper world (reverse (sortBy (\(a,_) (b,_) -> compare a b) new_hunters)) (sortBy (\(a,_) (b,_) -> compare a b) new_preys)
    where movedHunters = [ moveHunter world h | h <- hunters] 
          movedPreys = [movePrey world p | p <- preys]
          (new_hunters,survived_preys) = updateBoth world movedHunters movedPreys []
          trappedPreys = [p | p <- survived_preys, world!!snd(snd p)!!fst(snd p)==T]
          new_preys = [ if p`elem`trappedPreys then (decreasePreyEnergy10 p) else p | p <- survived_preys]
simulate world = simulate_helper world hunters preys
    where hunters = reverse(sortBy (\(a,_) (b,_) -> compare a b) (myHunters world))
          preys = sortBy (\(a,_) (b,_) -> compare a b) (myPreys world)



