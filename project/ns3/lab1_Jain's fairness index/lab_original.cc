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


  // TO DO (2) - Construct Flow and Create Net
  /*
  	hint : Construct Flow -> ppt p4 second item
  	hint : Create Net -> You need to modify the {} and xxx contents
  		NetDeviceContainer {net_devices} = {flow1}.Install (nodes.Get (xxx), nodes.Get (xxx));
  		{net_devices}.Add({flow2}.Install(nodes.Get(xxx), nodes.Get(xxx)));
  */

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

