#!/bin/bash
dur=120
gap=10
wnop="wnoutput.csv"
echo "System_Timestamp,SSID,BSSID,Signal_Strength,Bit_Rate,Transmission_Power,Frequency_Band" > $wnop
for ((i=0;i<=$dur;i+=$gap))
do
    System_Timestamp=$(date +%H:%M:%S)
    SSID=$(iwconfig wlp0s20f3|grep -i --color "ESSID" | awk '{print $4}' | cut -d':' -f2 | tr -d '"')
    BSSID=$(iwconfig wlp0s20f3 | grep -i --color "Access Point" | awk '{print $6}')
    Signal_Strength=$(iwconfig wlp0s20f3 | grep -i --color "Signal level" | awk '{print $4}' | tr -d 'dBm')
    Bit_Rate=$(iwconfig wlp0s20f3 | grep -i --color "Bit Rate" | awk '{print $2}' | tr -d 'Mb/s')
    Transmission_Power=$(iwconfig wlp0s20f3 | grep -i --color "Tx-Power" | awk '{print $4}' | tr -d 'dBm')
    Frequency_Band=$(iwconfig wlp0s20f3 | grep -i --color "Frequency" | awk '{print $2}' | tr -d 'GHz')
    echo "$System_Timestamp,$Signal_Strength,$Bit_Rate"
    echo "$System_Timestamp,$SSID,$BSSID,${Signal_Strength//[^0-9]/},${Bit_Rate//[^0-9]/},${Transmission_Power//[^0-9]/},${Frequency_Band//[^0-9]/}" >> $wnop
    sleep $gap
done
