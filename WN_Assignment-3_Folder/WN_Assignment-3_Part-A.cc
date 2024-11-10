#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"
#include "ns3/point-to-point-module.h"
#include <fstream>
#include <string>

using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("WN_Assign-3");

// Collision and reception counters
int totalreceptions=0;
int totalcollisions=0;

void PacketReception(std::string context, Ptr<const Packet> packet, double snr, WifiMode mode, WifiPreamble preamble) {
    totalreceptions++;
}

void PacketCollision(std::string context, Ptr<const Packet> packet, double snr) {
    totalcollisions++;
}

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
    NodeContainer p2p_nodes;
    NetDeviceContainer p2p_device;
    p2p_nodes.Add(ap_node);
    p2p_nodes.Add(server_node);
    p2p_device = p2pconn.Install(p2p_nodes);
    
    // Wifi setup
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211n);
    wifi.SetRemoteStationManager("ns3::MinstrelHtWifiManager");
    YansWifiPhyHelper phy;
    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();
    wifiChannel.AddPropagationLoss("ns3::ThreeLogDistancePropagationLossModel");
    wifiChannel.AddPropagationLoss("ns3::NakagamiPropagationLossModel");
    phy.SetChannel(wifiChannel.Create());
    
    WifiMacHelper mac;
    Ssid ssid=Ssid("ns-3-ssid");

    // AP
    mac.SetType("ns3::ApWifiMac","Ssid",SsidValue(ssid));
    NetDeviceContainer ap_device=wifi.Install(phy,mac,ap_node.Get(0));

    // STAs
    mac.SetType("ns3::StaWifiMac","Ssid", SsidValue(ssid));
    NetDeviceContainer sta_devices=wifi.Install(phy,mac,sta_nodes);
    
    MobilityHelper mobility;
    mobility.SetPositionAllocator("ns3::GridPositionAllocator","MinX",DoubleValue(0.0),"MinY", DoubleValue(0.0),"DeltaX",DoubleValue(1),"DeltaY", DoubleValue(0.0),"GridWidth",UintegerValue(2),"LayoutType", StringValue("RowFirst"));
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ap_node);
    mobility.Install(sta_nodes);
    mobility.Install(server_node);
    
    // Install internet stack
    InternetStackHelper internet;
    internet.Install(ap_node);
    internet.Install(sta_nodes);
    internet.Install(server_node);
    
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0","255.255.255.0");
    Ipv4InterfaceContainer p2p_interface;
    p2p_interface=address.Assign(p2p_device);
 
    address.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer ap_interface;
    Ipv4InterfaceContainer sta_interface;
    ap_interface=address.Assign(ap_device);
    sta_interface=address.Assign(sta_devices);
    
    int bs_port=9;
    int oo_port=40;
    
    for (int i=0;i<20;i++){
        BulkSendHelper source("ns3::TcpSocketFactory",InetSocketAddress(sta_interface.GetAddress(i),bs_port));
        source.SetAttribute("MaxBytes",UintegerValue(5*1024*1024));
        ApplicationContainer sourceApps=source.Install(server_node.Get(0));
        sourceApps.Start(Seconds(0.0));
        sourceApps.Stop(Seconds(10.0));
        
        PacketSinkHelper sink("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(),bs_port));
        ApplicationContainer sinkApps=sink.Install(sta_nodes.Get(i));
        sinkApps.Start(Seconds(0.0));
        sinkApps.Stop(Seconds(10.0));
        bs_port+=1;
        
        OnOffHelper source2("ns3::TcpSocketFactory",InetSocketAddress(p2p_interface.GetAddress(1),oo_port));
        source2.SetAttribute("DataRate",StringValue("200Kbps"));
        ApplicationContainer sourceApps2=source2.Install(sta_nodes.Get(i));
        sourceApps2.Start(Seconds(1.0));
        sourceApps2.Stop(Seconds(10.0));
        
        PacketSinkHelper sink2("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(),oo_port));
        ApplicationContainer sinkApps2=sink2.Install(server_node.Get(0));
        sinkApps2.Start(Seconds(0.0));
        sinkApps2.Stop(Seconds(10.0));
        oo_port+=1;
    }
    Ipv4GlobalRoutingHelper::PopulateRoutingTables(); 
    p2pconn.EnablePcapAll("wired_capture",false);
    phy.EnablePcapAll("wireless_capture", false);

    // Connect to reception and collision events
    Config::Connect("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/State/RxOk", MakeCallback(&PacketReception));
    Config::Connect("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/State/RxError", MakeCallback(&PacketCollision));


    
    Simulator::Stop(Seconds(10.0));
    
    Simulator::Run();
    
    // Calculate collision percentage
    double collisionPercentage=(totalcollisions/(double)(totalreceptions+totalcollisions))*100;
    std::cout<<"Collision Percentage: "<<collisionPercentage<<"%"<<std::endl;

    Simulator::Destroy();
}

