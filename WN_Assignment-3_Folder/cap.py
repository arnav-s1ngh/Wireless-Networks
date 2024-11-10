import pandas as pd
cap=pd.read_csv("tcpsend.csv")
for i in range(2, 22):
    dest="10.1.2." + str(i)
    tim=[]
    for noth,row in cap.iterrows():
        if row['Destination']==dest:
            tim.append(row['Time'])
    if tim!=[]:
        print(dest,max(tim)-min(tim))
