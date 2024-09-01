import matplotlib.pyplot as plt
import pandas as pd
wn_data=pd.read_csv("wnoutput.csv")
timestamps=wn_data["System_Timestamp"]
print(timestamps)
sigstrength=wn_data["Signal_Strength"]
sigstrength=[i*(-1) for i in sigstrength]
print("Signal Strengths", sigstrength)
bitrate=wn_data["Bit_Rate"]
bitrate=list(bitrate)
for i in range(len(bitrate)-6):
    bitrate[i]=bitrate[i]*0.1
print("Bit Rates:- ",bitrate)
plt.subplot(1, 2, 1)
plt.plot(timestamps,sigstrength,label="Signal Strength",color="blue")
plt.xticks(rotation=47)
plt.xlabel("Time in HH:MM:SS format")
plt.ylabel("Signal Strength in dBm")
plt.subplot(1, 2, 2)
plt.plot(timestamps,bitrate,label="Bit Rate",color="green")
plt.xticks(rotation=47)
plt.xlabel("Time in HH:MM:SS format")
plt.ylabel("Signal Strength in Mb/s")
plt.show()

