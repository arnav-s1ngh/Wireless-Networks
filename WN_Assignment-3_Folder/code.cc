#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"
#include <fstream>
#include <string>

// Network Topology
//                                       Wifi          P2P                  
//  (n20 n19 n18 ................. n1)=========AP--------------------------Server
//     Path Loss+Fading                             Delay:- 100 ms
//     MinstrelHTWifiManager                        Bandwidth:- 1000 Mbps


using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("WN_Assign-3");

int main(){

    int nw=20; //Number of STAs in the WiFi network
    NodeContainer sta_nodes;
    sta_nodes.Create(nw);
    
    NodeContainer ap_node; // AP
    ap_node.Create(1);
    
    NodeContainer server_node; // Server
    server_node.Create(1);
    
    // Establish Server-AP P2P Connection
    PointToPointHelper p2pconn;
    p2pconn.SetDeviceAttribute("DataRate",StringValue("1000Mbps"));
    p2pconn.SetChannelAttribute("Delay",StringValue("100ms"));
    
    NetDeviceContainer p2pDevices;
    p2p_server_device=p2pconn.Install(server_node.Get(0));
    p2p_ap_device=p2pconn.Install(ap_node.Get(0));
    
    //Wifi
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211n);
    wifi.SetRemoteStationManager("ns3::MinstrelHtWifiManager");
    YansWifiPhyHelper phy;
    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();
    phy.SetChannel(wifiChannel.Create());
    
    WifiMacHelper mac;
    Ssid ssid=Ssid("ns-3-ssid");
    
    //AP
    mac.SetType("ns3::ApWifiMac","Ssid",SsidValue(ssid));
    NetDeviceContainer apdevice=wifi.Install(phy,mac,ap_node.Get(0));

    //STAs
    mac.SetType("ns3::StaWifiMac","Ssid", SsidValue(ssid));
    NetDeviceContainer staDevices=wifi.Install(phy,mac,sta_nodes);
    
    MobilityHelper mobility;
    mobility.SetPositionAllocator("ns3::GridPositionAllocator","MinX",DoubleValue(0.0),"MinY", DoubleValue(0.0),"DeltaX",DoubleValue(5.0),"DeltaY", DoubleValue(0.0),"GridWidth",UintegerValue(2),"LayoutType", StringValue("RowFirst"));
    
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ap_node);
    mobility.Install(sta_nodes);
    mobility.Install(server_node);
    
    // Install internet stack
    InternetStackHelper internet;
    internet.Install(ap_node);
    internet.Install(sta_nodes);
    internet.install(server_node);
}




