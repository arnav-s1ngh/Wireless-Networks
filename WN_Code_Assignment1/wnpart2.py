import matplotlib.pyplot as plt
import pandas as pd
import re
# wn_data=pd.read_csv("dist_capture.csv")
# print(wn_data)

#Part A
beacondata=pd.read_csv("beacons.csv")
print(list(beacondata["SSID"]))
print(list(set(list(beacondata["SSID"]))), len(beacondata["SSID"]))
ssid_data=list(beacondata["SSID"])
print(" ")

#Part-B
print(list(beacondata["Data rate (Mb/s)"]))
bitrate=list(beacondata["Data rate (Mb/s)"])
print("The Average Bit Rate is:-", sum(bitrate)/len(bitrate),"Mb/s")
print(" ")

#Part C
sigstren=[int(i[0:3]) for i in list(beacondata["Signal strength (dBm)"])]
print(sigstren, len(sigstren))
print("The Average Signal Strength is:-", sum(sigstren)/len(sigstren),"dBm")
print(" ")

#after the prelim completion, creating functions to find avg for each ap since i didn't read the fricking fine lines
def indivavg(ssid_set):
    for j in ssid_set:
        loc_b = []
        loc_s = []
        for i in range(len(bitrate)):
            if ssid_data[i]==j:
                loc_s.append(sigstren[i])
                loc_b.append(bitrate[i])
        print("the avg sigstren and bitrate for ", j, "is ",sum(loc_s)/len(loc_s),"dBm and ", sum(loc_b)/len(loc_b), "Mb/s respectively")
print(indivavg((list(set(list(beacondata["SSID"]))))))
print(" ")

#Part D
d1d2=pd.read_csv("d1d2packets.csv")
print("The total number of D1-D2 frames are ",len(list(d1d2["Data rate (Mb/s)"])), ", they are all QoS data frames")
print("Number of Types of Frames is ", len(set(list(d1d2['Type/Subtype']))))
if len(set(list(d1d2['Type/Subtype'])))==1:
    print(set(list(d1d2['Type/Subtype'])),len(list(d1d2["Type/Subtype"])))
print(" ")

#Part E
acks=pd.read_csv("acks.csv")
bitrate_acks=list(acks["Data rate (Mb/s)"])
print("The Average Bit Rate for ACKs is:-", sum(bitrate_acks)/len(bitrate_acks),"Mb/s")

#Part F
bitrate_d1d2=list(d1d2["Data rate (Mb/s)"])
sigstren_d1d2=[int(i[0:3]) for i in list(d1d2["Signal strength (dBm)"])]
print("The Average Signal Strength is:-", sum(sigstren_d1d2)/len(sigstren_d1d2),"dBm")
print("The Average Bit Rate for D1-D2 packets is:-", sum(bitrate_d1d2)/len(bitrate_d1d2),"Mb/s")

#Part G
print("CC D1 D2 CAPTURES")
cc=pd.read_csv("close_capture_d1d2.csv")
bitrate_cc=list(cc["Data rate (Mb/s)"])
sigstren_cc=[int(i[0:3]) for i in list(cc["Signal strength (dBm)"])]
print("The Average Signal Strength is:-", sum(sigstren_cc)/len(sigstren_cc),"dBm")
print("The Average Bit Rate for D1-D2 packets is:-", sum(bitrate_cc)/len(bitrate_cc),"Mb/s")
