#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/wifi-mac-helper.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/mobility-helper.h"
#include <ctime>
using namespace ns3;
NS_LOG_COMPONENT_DEFINE("WN_Assignment-2");
int main(int argc, char* argv[]) {
   Time::SetResolution(Time::NS);
   LogComponentEnable("UdpEchoClientApplication",LOG_LEVEL_INFO);
   LogComponentEnable("UdpEchoServerApplication",LOG_LEVEL_INFO);
   int nw=5;
   NodeContainer p2p_nodes;
   p2p_nodes.Create(2); // Server and AP
   NodeContainer wifi_nodes;
   wifi_nodes.Create(nw); // WiFi Nodes
   PointToPointHelper p2pconn;
   p2pconn.SetDeviceAttribute("DataRate",StringValue("1000Mbps"));
   p2pconn.SetChannelAttribute("Delay",StringValue("100ms"));
   NetDeviceContainer p2p_devices;
   p2p_devices=p2pconn.Install(p2p_nodes);

   //https://github.com/named-data-ndnSIM/ndnSIM/blob/master/examples/ndn-simple-wifi.cpp, used this to select the path loss and fading models
   YansWifiChannelHelper channel=YansWifiChannelHelper::Default();
   channel.AddPropagationLoss("ns3::ThreeLogDistancePropagationLossModel");
   channel.AddPropagationLoss("ns3::NakagamiPropagationLossModel");
   YansWifiPhyHelper phy;
   phy.SetChannel(channel.Create()); // Unlike Ethernet, AP not added to NodeContainer
   WifiMacHelper mac;
   Ssid ssid=Ssid("ns-3-ssid");
   WifiHelper wifi;
   wifi.SetRemoteStationManager("ns3::MinstrelHtWifiManager");
   Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue("0"));
   NetDeviceContainer wifi_devices;
   NetDeviceContainer ap_device;
   mac.SetType("ns3::StaWifiMac","Ssid",SsidValue(ssid));
   wifi_devices=wifi.Install(phy,mac,wifi_nodes);
   mac.SetType("ns3::ApWifiMac","Ssid",SsidValue(ssid));
   ap_device=wifi.Install(phy,mac,p2p_nodes.Get(1));


   MobilityHelper mobility;
   mobility.SetPositionAllocator("ns3::GridPositionAllocator","MinX", DoubleValue(0.0),"MinY", DoubleValue(0.0),"DeltaX", DoubleValue(5.0),"DeltaY", DoubleValue(10.0),"GridWidth", UintegerValue(3),"LayoutType", StringValue("RowFirst"));
   mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
   mobility.Install(wifi_nodes);
   mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
   mobility.Install(p2p_nodes);


   InternetStackHelper stack;
   stack.Install(wifi_nodes);
   stack.Install(p2p_nodes);


   Ipv4AddressHelper address;
   address.SetBase("10.1.1.0", "255.255.255.0");
   Ipv4InterfaceContainer p2p_interfaces = address.Assign(p2p_devices);
   address.SetBase("10.1.2.0", "255.255.255.0");
   Ipv4InterfaceContainer wifi_interfaces = address.Assign(wifi_devices);
   address.Assign(ap_device);
   for(int cl_num=0;cl_num<nw;cl_num++){
      std::cout<<"Running Client "<<cl_num+1<<std::endl;
      BulkSendHelper source ("ns3::TcpSocketFactory", InetSocketAddress (wifi_interfaces.GetAddress (cl_num), 9+cl_num));
      source.SetAttribute ("MaxBytes", UintegerValue(5*1024*1024));
      ApplicationContainer sourceApps = source.Install (p2p_nodes.Get (0));
      sourceApps.Start (Seconds (0.0));
      sourceApps.Stop (Seconds (50.0));
   }
   for (int i = 0; i < nw; i++) {
      std::cout<<"Running Client "<<i+1<<std::endl;
      OnOffHelper onOffHelper ("ns3::TcpSocketFactory", InetSocketAddress (p2p_interfaces.GetAddress (0), 15+i));
      onOffHelper.SetAttribute ("DataRate", StringValue ("200Kbps"));
      ApplicationContainer uploadApp = onOffHelper.Install (wifi_nodes.Get(i));
      uploadApp.Start (Seconds(1.0));
      uploadApp.Stop (Seconds(50.0));
   }
   Ipv4GlobalRoutingHelper::PopulateRoutingTables(); 
   Simulator::Stop(Seconds(50.0));
   Time begin=Simulator::Now();
   p2pconn.EnablePcapAll("partd_p2p_pcap",false);
   phy.EnablePcapAll ("partd_wifi_pcap",false);
   Simulator::Run();
   Time end=Simulator::Now();
   Simulator::Destroy();
   std::cout<< "Simulation Time" << end-begin<< std::endl;
   return 0;
}
