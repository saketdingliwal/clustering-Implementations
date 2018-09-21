import sys
import matplotlib.pyplot as plt
import random

inpfile = sys.argv[1]
fname = sys.argv[2]

# print "aa gya"
with open(inpfile) as f:
	inpdata = f.readlines()
inpdata = [[float(f) for f in x.strip().split(" ")] for x in inpdata]


with open(fname) as f:
    content = f.readlines()
content = [x.strip() for x in content] 

# color_arr = ['red', 'blue', 'green', 'yellow', 'brown', 'purple']
color_arr = "rbgmcyk"

color_ind = -1

num_clusters = 0

for ele in content:
	if(ele[0]=='#'):
		num_clusters += 1
		if ele[1] == "o":
			color_ind = 6
		else:
			color_ind += 1
			color_ind = color_ind%6
	else:
		coord = [int(f) for f in ele.split(" ")]
		if color_ind==6:
			plt.plot(inpdata[coord[0]][0], inpdata[coord[0]][1], 'ro', color=color_arr[color_ind])
		elif random.uniform(0,1)<1:
			plt.plot(inpdata[coord[0]][0], inpdata[coord[0]][1], 'ro', color=color_arr[color_ind])

print(num_clusters-1)
plt.show()