import matplotlib.pyplot as plt
n=100
y=[50]*n
x=list(range(1,n+1))
plt.plot(x,y)
plt.xlabel("Nodes")
plt.ylabel("Time in Seconds")
plt.show()
