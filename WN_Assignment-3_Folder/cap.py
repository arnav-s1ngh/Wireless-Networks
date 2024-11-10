import matplotlib.pyplot as plt
import pandas as pd
cap=pd.read_csv("wireless_capture.csv")
lst=list(cap["Time"])
tim=[]
for i in range(20):
  tim.append(lst[len(lst)-(i+1)]-lst[i])
plt.plot(list(range(1,21)),tim)
plt.show()
