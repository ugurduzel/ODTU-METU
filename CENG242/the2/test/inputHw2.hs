h1 = H (Hunter 1 Expert 90 0 [E])
h2 = H (Hunter 2 Newbie 70 0 [W])
p1 = P (Prey 1 70 [S]) 
p2 = P (Prey 2 100 [S]) 
dunya = [
       [ O,p1, O, O],
       [h1, O,h2, O],
       [ O,p2, O, O]
                   ]
([(Hunter {hID = 1, hlevel = Expert, hEnergy = 100, hNumberOfCatches = 1, hActions = []},(1,1)),(Hunter {hID = 2, hlevel = Newbie, hEnergy = 69, hNumberOfCatches = 0, hActions = []},(1,1))],[(Prey {pID = 2, pEnergy = 99, pActions = []},(1,2))])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 90 0 [E])
h2 = H (Hunter 2 Newbie 70 0 [W])
p1 = P (Prey 1 70 [S]) 
p2 = P (Prey 2 100 [N]) 
dunya = [
       [ O,p1, O, O],
       [h1, O,h2, O],
       [ O,p2, O, O]
                   ]
([(Hunter {hID = 1, hlevel = Expert, hEnergy = 100, hNumberOfCatches = 2, hActions = []},(1,1)),(Hunter {hID = 2, hlevel = Newbie, hEnergy = 69, hNumberOfCatches = 0, hActions = []},(1,1))],[])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 90 0 [E,E])
h2 = H (Hunter 2 Newbie 70 0 [W,E])
p1 = P (Prey 1 70 [S,E]) 
p2 = P (Prey 2 100 [N,E]) 
dunya = [
       [ O,p1, O, O],
       [h1, O,h2, O],
       [ O,p2, O, O]
                   ]
([(Hunter {hID = 1, hlevel = Expert, hEnergy = 100, hNumberOfCatches = 2, hActions = [E]},(1,1)),(Hunter {hID = 2, hlevel = Newbie, hEnergy = 69, hNumberOfCatches = 0, hActions = [E]},(1,1))],[])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 90 0 [E,E])
h2 = H (Hunter 2 Newbie 70 0 [W,E])
p1 = P (Prey 1 70 [S,E]) 
p2 = P (Prey 2 100 [N,E]) 
dunya = [
       [ O,p1, O, O],
       [h1, X,h2, O],
       [ O,p2, O, O]
                   ]
([(Hunter {hID = 1, hlevel = Expert, hEnergy = 88, hNumberOfCatches = 0, hActions = []},(0,1)),(Hunter {hID = 2, hlevel = Newbie, hEnergy = 68, hNumberOfCatches = 0, hActions = []},(3,1))],[(Prey {pID = 1, pEnergy = 68, pActions = []},(2,0)),(Prey {pID = 2, pEnergy = 98, pActions = []},(2,2))])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 100 0 [E,E])
h2 = H (Hunter 2 Newbie 100 0 [E,W])
p1 = P (Prey 1 100 [W,W]) 
p2 = P (Prey 2 100 [S,S]) 
dunya = [
         [ O, O,p1,p2],
         [ O, X, X, T],
         [h1,h2, O, O]
                      ]
([(Hunter {hID = 1, hlevel = Expert, hEnergy = 98, hNumberOfCatches = 0, hActions = []},(2,2)),(Hunter {hID = 2, hlevel = Newbie, hEnergy = 98, hNumberOfCatches = 0, hActions = []},(1,2))],[(Prey {pID = 2, pEnergy = 88, pActions = []},(3,2)),(Prey {pID = 1, pEnergy = 98, pActions = []},(0,0))])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 100 0 [E,E,E,E])
h2 = H (Hunter 2 Newbie 100 0 [E,E,E,E])
p1 = P (Prey 1 33 [E,S,W,S]) 
p2 = P (Prey 2 49 [S,W,W,W]) 
dunya = [
         [ O, O,p1,p2],
         [ O, X, X, T],
         [h1,h2, O, O]
                      ]
([(Hunter {hID = 1, hlevel = Expert, hEnergy = 100, hNumberOfCatches = 1, hActions = []},(3,2)),(Hunter {hID = 2, hlevel = Newbie, hEnergy = 96, hNumberOfCatches = 0, hActions = []},(3,2))],[(Prey {pID = 2, pEnergy = 5, pActions = []},(3,1))])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 100 0 [E,E,E,E])
h2 = H (Hunter 2 Newbie 100 0 [E,E,E,E])
p1 = P (Prey 1 32 [E,S,W,S]) 
p2 = P (Prey 2 49 [S,W,W,W]) 
dunya = [
         [ O, O,p1,p2],
         [ O, X, X, T],
         [h1,h2, O, O]
                      ]
([(Hunter {hID = 1, hlevel = Expert, hEnergy = 96, hNumberOfCatches = 0, hActions = []},(3,2)),(Hunter {hID = 2, hlevel = Newbie, hEnergy = 96, hNumberOfCatches = 0, hActions = []},(3,2))],[(Prey {pID = 1, pEnergy = 0, pActions = []},(3,1)),(Prey {pID = 2, pEnergy = 5, pActions = []},(3,1))])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 10 0 [E])
h2 = H (Hunter 2 Newbie 100 0 [W])
p1 = P (Prey 1 60 [S]) 
p2 = P (Prey 2 80 [W]) 
p3 = P (Prey 3 70 [N]) 
dunya = [
         [ O, p1, O, O],
         [ h1, O,p2, O],
         [ O, p3, O, O]
                       ]
([(Hunter {hID = 1, hlevel = Expert, hEnergy = 49, hNumberOfCatches = 2, hActions = []},(1,1))],[(Prey {pID = 3, pEnergy = 89, pActions = []},(1,1))])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 90 0 [S])
h2 = H (Hunter 2 Expert 100 0 [N])
h3 = H (Hunter 3 Expert 80 0 [S])
h4 = H (Hunter 4 Expert 80 0 [N])
h5 = H (Hunter 5 Expert 80 0 [N])
p1 = P (Prey 1 60 [E]) 
p2 = P (Prey 2 80 [E]) 
p3 = P (Prey 3 70 [W]) 
dunya = [
         [ O, h1,h3, O],
         [ p1,p2,p3,h5],
         [ O, h2,h4, O]
                       ]
([(Hunter {hID = 2, hlevel = Expert, hEnergy = 100, hNumberOfCatches = 2, hActions = []},(1,1)),(Hunter {hID = 3, hlevel = Expert, hEnergy = 99, hNumberOfCatches = 1, hActions = []},(2,1)),(Hunter {hID = 1, hlevel = Expert, hEnergy = 89, hNumberOfCatches = 0, hActions = []},(1,1)),(Hunter {hID = 4, hlevel = Expert, hEnergy = 79, hNumberOfCatches = 0, hActions = []},(2,1)),(Hunter {hID = 5, hlevel = Expert, hEnergy = 79, hNumberOfCatches = 0, hActions = []},(3,0))],[])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 9 0 [W,S,W,W,S,S])
h2 = H (Hunter 2 Expert 100 0 [E,W,E,W,E,W])
p1 = P (Prey 1 60 [N,S,N,W,S,N]) 
p2 = P (Prey 2 16 [W,E,W,E,W,E]) 
dunya = [
         [ O,h1,h2, p2],
         [ O, X, O, O],
         [p1, O, O, O]
                       ]
([(Hunter {hID = 2, hlevel = Expert, hEnergy = 94, hNumberOfCatches = 0, hActions = []},(2,0)),(Hunter {hID = 1, hlevel = Expert, hEnergy = 29, hNumberOfCatches = 1, hActions = []},(0,1))],[(Prey {pID = 2, pEnergy = 10, pActions = []},(3,0))])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 9 0 [W,S,W,W,S,S])
h2 = H (Hunter 2 Expert 100 0 [E,W,E,W,E,W])
p1 = P (Prey 1 60 [N,S,N,W,S,N]) 
p2 = P (Prey 2 13 [W,E,W,E,W,E]) 
dunya = [
         [ O,h1,h2, p2],
         [ O, X, O, O],
         [p1, O, O, O]
                       ]
([(Hunter {hID = 2, hlevel = Expert, hEnergy = 99, hNumberOfCatches = 1, hActions = []},(2,0)),(Hunter {hID = 1, hlevel = Expert, hEnergy = 29, hNumberOfCatches = 1, hActions = []},(0,1))],[])
--------------------------------------------------------------------------------------------------------------
h1 = H (Hunter 1 Expert 9 0 [W,S,W,W,S,S])
h2 = H (Hunter 2 Expert 100 0 [E,W,E,W,E,W])
p1 = P (Prey 1 60 [N,S,N,W,S,N]) 
p2 = P (Prey 2 14 [W,E,W,E,W,E]) 
dunya = [
         [ O,h1,h2, p2],
         [ O, X, O, O],
         [ O, O, O, O]
                       ]
([(Hunter {hID = 2, hlevel = Expert, hEnergy = 100, hNumberOfCatches = 1, hActions = []},(2,0)),(Hunter {hID = 1, hlevel = Expert, hEnergy = 9, hNumberOfCatches = 0, hActions = []},(0,1))],[])
