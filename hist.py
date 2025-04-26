import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
	num_of_iter = 22;
	linear_data = []
	stupid_data = []
	genetic_data = []
	dynamic_data = []
	with open('avgs.txt', 'r') as file:
		for line in file.readlines():
				temp = line.split(' ')
				if float(temp[1]) > -1:
					dynamic_data.append(np.log(float(temp[1])))
				if float(temp[2]) > -1:
					genetic_data.append(np.log(float(temp[2])))
				if float(temp[3]) > -1:
					linear_data.append(np.log(float(temp[3])))
				if float(temp[4]) > -1:
					stupid_data.append(np.log(float(temp[4])))
	plt.plot(dynamic_data, color='red', label='dynamic')
	plt.plot(genetic_data, color='green', label='genetic')
	plt.plot(linear_data, color='blue', label='brute forse')
	plt.plot(stupid_data, color='orange', label='random')
	plt.title('Traveling Salesman Problem')
	plt.xlabel('number of cities')
	plt.ylabel('log(time)')
	plt.legend()
	plt.show()
	#for i in range(1, num_of_iter + 1):
	#	with open('a', 'r') as file:
	#		for line in file.readlines():
	#			temp = line.split(' ')
	#			linear_data.append(float(temp[0]))
	#			genetic_data.append(float(temp[1]))
	#	linear_averages[i - 1] = np.log(np.array(linear_data).mean())
	#	genetic_averages[i - 1] = np.log(np.array(genetic_data).mean())
	#	with open('test_results_' + str(i) + '_baseline.txt', 'r') as file:
	#		for line in file.readlines():
	#			temp = line.split(' ')
	#			genetic_data_base.append(float(temp[1]))
	#	genetic_averages_base[i - 1] = np.log(np.array(genetic_data_base).mean())
		#with open('test_results_' + str(i) + '_lowpop.txt', 'r') as file:
		#	for line in file.readlines():
		#		temp = line.split(' ')
		#		genetic_data_lowpop.append(float(temp[1]))
		#genetic_averages_lowpop[i - 1] = np.log(np.array(genetic_data_lowpop).mean())
		#with open('test_results_' + str(i) + '_lowpop2.txt', 'r') as file:
		#	for line in file.readlines():
		#		temp = line.split(' ')
		#		genetic_data_lowpop2.append(float(temp[1]))
		#genetic_averages_lowpop2[i - 1] = np.log(np.array(genetic_data_lowpop2).mean())
	#plt.plot(linear_averages, color = 'blue', label='brute forse')
	#plt.plot(genetic_averages_base, color = 'green', label='genetic algorithm, 100 population')
	#plt.plot(genetic_averages, color = 'red', label='genetic algorithm, 30 population')
	#plt.plot(genetic_averages_lowpop, color = 'orange', label='genetic algorithm, 100 population')
	#plt.plot(genetic_averages_lowpop2, color = 'purple', label='genetic algorithm, 60 population')
	#plt.legend()
	#plt.title('Traveling Salesman Problem')
	#plt.xlabel('number of cities')
	#plt.ylabel('log(time)')
	#plt.show()

	#ratios_data = []
	#with open('test_results_1.txt', 'r') as file:
	#	for line in file.readlines():
	#		temp = line.split(' ')
	#		linear_data.append(float(temp[0]))
	#		#stupid_data.append(float(temp[1]))
	#		gendumb_data.append(float(temp[1]))
	#		#ratios_data.append(float(temp[0])/float(temp[1]))
	#linear_times = np.array(linear_data)
	#stupid_times = np.array(stupid_data)
	#gendumb_times = np.array(gendumb_data)
	#ratios_times = np.array(ratios_data)
	#bins = np.linspace(0, 1, 100)
	#n, bins1, patches = plt.hist(linear_times, bins, color='blue', alpha=0.5)
	#n, bins1, patches = plt.hist(stupid_times, bins, color='red', alpha=0.3)
	#n, bins1, patches = plt.hist(gendumb_times, bins, color='green', alpha=0.5)
	#print(linear_times.mean())
	#print(stupid_times.mean())
	#print(gendumb_times.mean())
	#plt.show()
	#bins_r = np.linspace(0, 2, 200)
	#n, bins1, patches = plt.hist(ratios_times, bins_r)
	#plt.show()