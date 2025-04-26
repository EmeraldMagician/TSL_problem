import matplotlib.pyplot as plt
import numpy as np

def factorial(n):
	z = 1
	for i in range(n):
		z *= (i + 1)
	return z

arr = []
ind = list(range(3, 20))
arr2 = []
labels = ['dynamic', 'genetic', '2opt', 'lkh', 'linear', 'random']

i = 0
with open('temp.txt') as file:
	for line in file.readlines():
		if i < len(ind):
			arr.append(line.split())
		else:
			arr2.append(line.split())
		i += 1
brr = [[float(y) for y in x] for x in arr]
brr2 = [[float(y) for y in x] for x in arr2]
nparr = np.array(brr)
nparr2 = np.array(brr2)
crr = [(i**2.2)/nparr[i][3] for i in range(0, len(nparr))]
#for i in range(6):
#	plt.plot(ind, np.log(nparr[:, i]), label=labels[i])
#plt.plot([x*10 for x in range(1, 21)], nparr2)
plt.plot(ind, crr)
plt.xlabel('number of cities')
plt.ylabel('n^2.2/(LKH execution time)')
#plt.xlabel('population')
#plt.ylabel('average execution time')
plt.legend()
plt.show()