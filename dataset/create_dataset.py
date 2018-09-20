from random import randint
import matplotlib.pyplot as plt

def getCoord(xs, ys, ind, tw):
	xc = xs + ind%tw
	yc = ys + ind//tw

	return (xc, yc)

def createM(numPoints, thickness, width, height, xs, ys):
	hatArea = width*thickness
	legArea = (height - thickness)*thickness
	ttlArea = hatArea + 3*legArea

	pnt_arr = []

	for i in range(0, numPoints):
		ci = randint(0, ttlArea-1)
		if(ci<hatArea):
			xy = getCoord(0, 0, ci, width)
		else:
			ci = ci - hatArea
			xy = getCoord((ci//legArea)*(width//2 - thickness//2), thickness, ci%legArea, thickness)
		pnt_arr.append((xy[0] + xs, height - xy[1] + ys))

	return pnt_arr

def createU(numPoints, thickness, width, height, xs, ys):
	hatArea = width*thickness
	legArea = (height - thickness)*thickness
	ttlArea = hatArea + 2*legArea

	pnt_arr = []

	for i in range(0, numPoints):
		ci = randint(0, ttlArea-1)
		if(ci<hatArea):
			xy = getCoord(0, 0, ci, width)
		else:
			ci = ci - hatArea
			xy = getCoord((ci//legArea)*(width - thickness), thickness, ci%legArea, thickness)
		pnt_arr.append((xy[0] + xs, xy[1] + ys))

	return pnt_arr

def createNoise(xs, ys, xe, ye, numPoints):
	
	pnt_arr = []

	for i in range(0, numPoints):
		xc = randint(xs, xe)
		yc = randint(ys, ye)
		pnt_arr.append((xc, yc))

	return pnt_arr

gwidth = 10000
gheight = 10000
gap = 775
thicks = 300
thickl = 3000
numPoints = 400
noise = 200

arrM = createM(numPoints, thicks, gwidth, gheight - thickl - gap, 0, gap + thickl)

for ele in arrM:
	plt.plot(ele[0], ele[1], 'ro')

arrU = createU(numPoints, thickl, gwidth - 2*(gap + thicks), gheight - thicks - gap, gap + thicks, 0)

for ele in arrU:
	plt.plot(ele[0], ele[1], 'ro', color='blue')

arrN = createNoise(0-noise, 0-noise, gwidth + noise, gheight + noise, numPoints//20)

for ele in arrN:
	plt.plot(ele[0], ele[1], 'ro', color='green')

plt.show()