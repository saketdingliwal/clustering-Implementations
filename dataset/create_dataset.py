from random import randint
import matplotlib.pyplot as plt

def getCoord(xs, ys, ind, tw):
	xc = xs + ind%tw
	yc = ys + int(ind/tw)

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
			xy = getCoord(int(ci/legArea)*int(width/2 - thickness/2), thickness, ci%legArea, thickness)
		pnt_arr.append((xy[0] + xs, xy[1] + ys))

	return pnt_arr



width = 10000
height = 6000
numPoints = 500
thickness = 500
arr = createM(numPoints, thickness, width, height, 0, 0)

for ele in arr:
	plt.plot(ele[0], ele[1], 'ro')

plt.show()