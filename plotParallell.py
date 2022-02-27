import matplotlib.pyplot as plt
  
names = []
marks = []
  
f = open('parallell.txt','r')
for row in f:
    row = row.split(' ')
    names.append(row[0])
    marks.append(int(row[1]))




plt.plot(names, marks)
plt.plot
  
plt.xlabel('Number of threads', fontsize = 12)
plt.ylabel('Speed up', fontsize = 12)
  
plt.title('Speed up as a function of threads for an adjacency matrix of size 1000', fontsize = 12)
plt.show()
