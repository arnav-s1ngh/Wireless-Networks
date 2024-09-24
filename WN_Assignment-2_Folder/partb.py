import matplotlib.pyplot as plt
import pandas as pd
cap=pd.read_csv("partbcapture.csv")
lst=list(cap["Time"])
print(lst)
t1=lst[len(lst)-1]-lst[0]
t2=lst[len(lst)-2]-lst[1]
t3=lst[len(lst)-3]-lst[2]
t4=lst[len(lst)-4]-lst[3]
t5=lst[len(lst)-5]-lst[4]
print(t1,t2,t3,t4,t5)
plt.plot([1,2,3,4,5],[t1,t2,t3,t4,t5])
plt.show()
