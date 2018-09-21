from random import randint
import matplotlib.pyplot as plt
import numpy as np

file = open("dataset4d1000000.txt", "w")

for i in range(0, 1000000):
	for j in range(0, 4):
		c = randint(0, 10000)
		file.write(str(c) + " ")
	file.write("\n")

for i in range(0, 1000000):
	for j in range(0, 4):
		c = randint(0, 10000)
		file.write(str(c+100000) + " ")
	file.write("\n")

exit()

def getCoord(xs, ys, ind, tw):
	xc = xs + ind%tw
	yc = ys + ind//tw

	return (xc, yc)

def createM(numPoints, thickness, width, height, xs, ys, marked_points):
	hatArea = width*thickness
	legArea = (height - thickness)*thickness
	ttlArea = hatArea + 3*legArea

	for i in range(0, numPoints):
		ci = randint(0, ttlArea-1)
		if(ci<hatArea):
			xy = getCoord(0, 0, ci, width)
		else:
			ci = ci - hatArea
			xy = getCoord((ci//legArea)*(width//2 - thickness//2), thickness, ci%legArea, thickness)
		marked_points.append((xy[0] + xs, height - xy[1] + ys, 1))

	return marked_points

def createU(numPoints, thickness, width, height, xs, ys, marked_points):
	hatArea = width*thickness
	legArea = (height - thickness)*thickness
	ttlArea = hatArea + 2*legArea

	for i in range(0, numPoints):
		ci = randint(0, ttlArea-1)
		if(ci<hatArea):
			xy = getCoord(0, 0, ci, width)
		else:
			ci = ci - hatArea
			xy = getCoord((ci//legArea)*(width - thickness), thickness, ci%legArea, thickness)
		marked_points.append((xy[0] + xs, xy[1] + ys, 2))

	return marked_points

def createNoise(numPoints, noise, width, height, xs, ys, marked_points):
	widthPatch = width*noise
	heightPatch = (height-2*noise)*noise
	ttlArea = 2*(widthPatch + heightPatch)

	for i in range(0, numPoints):
		ci = randint(0, ttlArea-1)
		if(ci<widthPatch):
			xy = getCoord(0, 0, ci, width)
		elif(ci<2*widthPatch):
			xy = getCoord(0, height - noise, ci - widthPatch, width)
		elif(ci-2*widthPatch<heightPatch):
			xy = getCoord(0, noise, ci - 2*widthPatch, noise)
		else:
			xy = getCoord(width-noise, noise, ci - 2*widthPatch - heightPatch, noise)
		marked_points.append((xy[0] + xs, xy[1] + ys, 3))

	return marked_points

gwidth = 10900
gheight = 11000
gap = 1000
thicks = 300
thickl = 3000
numPoints = 500000
noise = 1000

mult = 2000

gwidth = mult*gwidth
gheight = mult*gheight
gap = mult*gap
thicks = mult*thicks
thickl = mult*thickl
noise = mult*noise

marked_points = []

# Index for M = 1
# Index for U = 2
# Index for outliers/Noise = 3

marked_points = createM(numPoints, thicks, gwidth, gheight - thickl - gap, noise, gap + thickl + noise, marked_points)

print("M made")

marked_points = createU(numPoints, thickl, gwidth - 2*(gap + thicks), gheight - thicks - gap, gap + thicks + noise, noise, marked_points)

print("U made")

marked_points = createNoise(numPoints//20, noise, gwidth + 2*noise, gheight + 2*noise, 0, 0, marked_points)

print("Noise added")

file = open("dataset1000000.txt", "w")

for ele in marked_points:
	i = ele[0]
	j = ele[1]

	file.write(str(i) + " " + str(j) + "\n")
	continue

	fd = ele[2]
	if(fd==1):
		plt.plot(i, j, 'ro', color='red')
	elif(fd==2):
		plt.plot(i, j, 'ro', color='red')
	elif(fd==3):
		plt.plot(i, j, 'ro', color='red')

# plt.show()