import matplotlib.pyplot as plt
import pandas as pd
cap=pd.read_csv("partbcapture.csv")
cap2=pd.read_csv("partccapture.csv")
lst=list(cap["Time"])
lst2=list(cap2["Time"])
t1=lst[len(lst)-1]-lst[0]
t2=lst[len(lst)-2]-lst[1]
t3=lst[len(lst)-3]-lst[2]
t4=lst[len(lst)-4]-lst[3]
t5=lst[len(lst)-5]-lst[4]
at1=lst2[len(lst2)-1]-lst2[0]
at2=lst2[len(lst2)-2]-lst2[1]
at3=lst2[len(lst2)-3]-lst2[2]
at4=lst2[len(lst2)-4]-lst2[3]
at5=lst2[len(lst2)-5]-lst2[4]
print(t1,t2,t3,t4,t5)
print(at1,at2,at3,at4,at5)
plt.plot([1,2,3,4,5],[t1,t2,t3,t4,t5],label="Part B")
plt.plot([1,2,3,4,5],[at1,at2,at3,at4,at5],label="Part C")
plt.legend(loc="lower right")
plt.xlabel("Nodes")
plt.ylabel("Time Taken")
plt.show()
