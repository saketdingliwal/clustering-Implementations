import sys
import matplotlib.pyplot as plt

fname = sys.argv[1]

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
		plt.plot(coord[0], coord[1], 'ro', color="rbgkm"[color_ind])

plt.show()