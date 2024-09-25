import matplotlib.pyplot as plt
import pandas as pd
cap=pd.read_csv("partbcapture.csv")
cap2=pd.read_csv("partccapture.csv")
cap3=pd.read_csv("partdcapture.csv")
cap4=pd.read_csv("partecapture.csv")
lst=list(cap["Time"])
lst2=list(cap2["Time"])
lst3=list(cap3["Time"])
lst4=list(cap4["Time"])
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
bt1=lst3[len(lst3)-1]-lst3[0]
bt2=lst3[len(lst3)-2]-lst3[1]
bt3=lst3[len(lst3)-3]-lst3[2]
bt4=lst3[len(lst3)-4]-lst3[3]
bt5=lst3[len(lst3)-5]-lst3[4]
ct1=lst4[len(lst4)-1]-lst4[0]
ct2=lst4[len(lst4)-2]-lst4[1]
ct3=lst4[len(lst4)-3]-lst4[2]
ct4=lst4[len(lst4)-4]-lst4[3]
ct5=lst4[len(lst4)-5]-lst4[4]
print(t1,t2,t3,t4,t5)
print(at1,at2,at3,at4,at5)
print(bt1,bt2,bt3,bt4,bt5)
print(ct1,ct2,ct3,ct4,ct5)
plt.plot([1,2,3,4,5],[t1,t2,t3,t4,t5],label="Part B")
plt.plot([1,2,3,4,5],[at1,at2,at3,at4,at5],label="Part C")
plt.plot([1,2,3,4,5],[bt1,bt2,bt3,bt4,bt5],label="Part D")
plt.plot([1,2,3,4,5],[ct1,ct2,ct3,ct4,ct5],label="Part E")
plt.legend(loc="lower right")
plt.xlabel("Nodes")
plt.ylabel("Time Taken")
plt.show()
