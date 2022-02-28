from cProfile import label
import matplotlib.pyplot as plt
  
serialList = []
serialNumbers = []
paralellList = []
paralellNum = []
  
serial = open('performanceSerial.txt','r')
for row in serial:
    row = row.split(' ')
    serialList.append(row[0])
    serialNumbers.append(float(row[1]))

paralell = open('performanceParallel.txt','r')
for row in paralell:
    row = row.split(' ')
    paralellList.append(row[0])
    paralellNum.append(float(row[1]))


plt.plot(serialList, serialNumbers, label = "Serial")
plt.plot(paralellList, paralellNum, label = "Parallel with 16 threads")
plt.legend()
plt.xlabel('Number of elements in adjacency matrix ', fontsize = 12)
plt.ylabel('Time', fontsize = 12)
plt.title('Execution time as function of elements in adjacency matrix', fontsize = 12)
plt.show()
