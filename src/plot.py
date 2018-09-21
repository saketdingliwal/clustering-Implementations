import sys
import matplotlib.pyplot as plt

print "hrllo"
inp_file = sys.argv[1]
X = []
with open(inp_file,"r") as f:
	reach_list = f.readlines()
for reach in reach_list:
	X.append(float(reach))

plt.plot(X)
plt.ylabel('reachability')
plt.savefig('optics.jpeg')
