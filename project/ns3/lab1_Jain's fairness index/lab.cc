#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/core-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/flow-monitor.h"
#include <cmath>

using namespace ns3;
using namespace std;

int main (int argc, char *argv[]){
  // construct simulation
  Time::SetResolution (Time::NS);

  NodeContainer nodes;

  // TO DO (1) - Construct three nodes
  /*
  	hint : ppt p4 first item
  */
  nodes.Create(3);

//==============================================================================

  // TO DO (2) - Construct Flow and Create Net
  /*
  	hint : Construct Flow -> ppt p4 second item
  	hint : Create Net -> You need to modify the {} and xxx contents
  		NetDeviceContainer {net_devices} = {flow1}.Install (nodes.Get (xxx), nodes.Get (xxx));
  		{net_devices}.Add({flow2}.Install(nodes.Get(xxx), nodes.Get(xxx)));
  */

//flow 1
  PointToPointHelper flow1;
  flow1.SetDeviceAttribute("DataRate", DataRateValue(DataRate("5Mbps")));
  flow1.SetChannelAttribute("Delay", TimeValue(MilliSeconds(10)));

//flow 2
  PointToPointHelper flow2;
  flow2.SetDeviceAttribute("DataRate", DataRateValue(DataRate("10Mbps")));
  flow2.SetChannelAttribute("Delay", TimeValue(MilliSeconds(20)));

  NetDeviceContainer devices = flow1.Install(nodes.Get(0) , nodes.Get(1) );
  devices.Add (flow2.Install(nodes.Get(1) , nodes.Get(2)));

//==============================================================================

  // install stack
  InternetStackHelper stack;
  stack.Install (nodes);

  // allocate ip address
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfacesAB = address.Assign (devices);

  // construct UDP protocal
  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (2)); // install server on node 2
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfacesAB.GetAddress (0), 9); // create application on node 0
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0)); // install application on node 0
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  // TO DO (3) - Output Throughput and Jain's Fairness Index
  /*
  	hint : ppt p7
	Please follow below output format
  		cout << "Throughput between Node A and Node B : " << throughputAB << " Mbps" << endl;
  		cout << "Throughput between Node B and Node C : " << throughputBC << " Mbps" << endl;
  		cout << "Jain's Fairness Index : " << your result of Jain's fairness index << endl;
  */

DataRateValue dataratevalueAB;
devices.Get(1)->GetAttribute("DataRate",dataratevalueAB);
DataRate dataRateAB = dataratevalueAB.Get();
double throughputAB = dataRateAB.GetBitRate()/1e6;

DataRateValue dataratevalueBC;
devices.Get(2)->GetAttribute("DataRate",dataratevalueBC);
DataRate dataRateBC = dataratevalueBC.Get();
double throughputBC = dataRateBC.GetBitRate()/1e6;

cout << endl;
cout << "========================      Jain's Fairness Index      ========================" << endl;
cout << endl;


double fairnessIndex = (throughputAB + throughputBC) * (throughputAB + throughputBC)
                      / (2.0 * (throughputAB * throughputAB + throughputBC * throughputBC));

cout << "Throughput between Node A and Node B : " << throughputAB << " Mbps" << endl;
cout << "Throughput between Node B and Node C : " << throughputBC << " Mbps" << endl;
cout << "Jain's Fairness Index : " <<  fairnessIndex << endl;


cout << endl;
cout << "========================Jain's Fairness Index with Weight========================" << endl;
cout << endl;

int weightAB = 2 ;
int weightBC = 1 ;
double weightfairnessIndex = (weightAB * throughputAB + weightBC * throughputBC) * (weightAB * throughputAB + weightBC * throughputBC)
                      / (2.0 * (weightAB * throughputAB * weightAB * throughputAB + weightBC * throughputBC * weightBC * throughputBC));

cout << "Throughput between Node A and Node B : " << throughputAB << " Mbps" << endl;
cout << "Weight     between Node A and Node B : " << weightAB << endl;
cout << "Throughput between Node B and Node C : " << throughputBC << " Mbps" << endl;
cout << "Weight     between Node B and Node C : " << weightBC << endl;
cout << "Jain's Fairness Index with weight : " <<  weightfairnessIndex << endl;

  FlowMonitorHelper flowMonitor;
  Ptr<FlowMonitor> monitor = flowMonitor.InstallAll();

  // start simulator
  Simulator::Stop (Seconds (10));
  Simulator::Run ();
  Simulator::Destroy ();
  
  /*
  	PLEASE DO NOT MODIFY BELOW CODE !!!
	It will used to check your flows constructed successfully or not.
  */
  cout << endl << "Check Flow Constructed Successfully Or Not : ";
  monitor->CheckForLostPackets (); // check loss packet or not
  FlowMonitor::FlowStatsContainer stats = monitor->GetFlowStats ();

  for (map<FlowId, FlowMonitor::FlowStats>::const_iterator it = stats.begin (); it != stats.end (); ++it) {
    FlowMonitor::FlowStats flowStats = it->second;
    if (flowStats.rxPackets > 0) {
      cout << "Flow succeeded." << endl;
    } else {
      cout << "Flow failed." << endl;
    }
  }

  return 0;
}

