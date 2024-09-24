import matplotlib.pyplot as plt
y1=[49,37,9,8,8]
y2=[47,17,17,17,20]
x=list(range(1,6))
plt.plot(x,y)
plt.plot(x,y2)
plt.xlabel("Nodes")
plt.ylabel("Time in Seconds")
plt.show()
