import random

def directionGenerator(row,col):
	result = "["
	pool = ["("+i+","+j+")" for i in ['N','S','W','E'] for j in ['N','S','W','E']]
	for move in range(50):
		result += pool[random.randint(0,15)]+','
	result = result[:-1]
	result += "]"
	return result		

def inputGenerator(row,col):
	hunter = list()
	prey = list()
	obstacle = list()
	for i in range(13):
		obstacle.append( (random.randint(0,row-1),random.randint(0,col-1)) )
	hunter.append( (random.randint(0,row-1),random.randint(0,col-1)) )
	prey.append( (random.randint(0,row-1),random.randint(0,col-1)) )
	while hunter==prey or hunter in obstacle or prey in obstacle:
		hunter.clear()
		prey.clear()
		hunter.append( (random.randint(0,row-1),random.randint(0,col-1)) )
		prey.append( (random.randint(0,row-1),random.randint(0,col-1)) )
	finalStr = "simulate ["
	for _row in range(row):
		finalStr += "["
		for _col in range(col):
			if _row==hunter[0][0] and _col==hunter[0][1]:
				finalStr += "H,"
			elif _row==prey[0][0] and _col==prey[0][1]:
				finalStr += "P,"
			elif len(obstacle)!=0 and (_row,_col) in obstacle:
				finalStr += "X,"
				obstacle.remove((_row,_col))
			else:
				finalStr += "O,"
		finalStr = finalStr[:-1]
		finalStr += "],"
	finalStr = finalStr[:-1]	
	finalStr += "] " + directionGenerator(row,col) 
	return finalStr

for i in range(250):
	print(inputGenerator(7,7))
