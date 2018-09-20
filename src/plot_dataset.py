import sys
import matplotlib.pyplot as plt

inpfile = sys.argv[1]
fname = sys.argv[2]

with open(inpfile) as f:
	inpdata = f.readlines()
inpdata = [[int(f) for f in x.strip().split(" ")] for x in inpdata]


with open(fname) as f:
    content = f.readlines()
content = [x.strip() for x in content] 

# color_arr = ['red', 'blue', 'green', 'yellow', 'brown', 'purple']

color_ind = 0

for ele in content:
	if(ele[0]=='#'):
		color_ind += 1
	else:
		coord = [int(f) for f in ele.split(" ")]
		plt.plot(inpdata[coord[0]][0], inpdata[coord[0]][1], 'ro', color="rbgkm"[color_ind])

plt.show()