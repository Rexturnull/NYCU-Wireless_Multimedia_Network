#include "../build/ns3/core-module.h"
#include "../build/ns3/network-module.h"
#include "../build/ns3/internet-module.h"
#include "../build/ns3/point-to-point-module.h"
#include "../build/ns3/traffic-control-module.h"
#include "../build/ns3/flow-monitor-module.h"
#include "../build/ns3/applications-module.h"
#include "../build/ns3/fifo-queue-disc.h"
#include "../build/ns3/packet.h"
#include "ns3/flow-monitor-module.h"
#include <iomanip>
#include <vector>


using namespace ns3;

int main() {

    // 網絡拓撲創建
    NodeContainer nodes;
    nodes.Create(2);

    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("500bps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("5ms")); 

    NetDeviceContainer devices;
    devices = pointToPoint.Install(nodes);

    // 創建一個FIFO隊列
    Ptr<QueueDisc> queue = CreateObject<FifoQueueDisc>();

    // 安裝網絡協議棧
    InternetStackHelper internet;
    internet.Install(nodes);

    // 分配IP地址
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    // 將隊列與設備關聯
    TrafficControlHelper tch;
    tch.Install(devices);
    QueueSize queueSize = QueueSize("200B"); 
    tch.SetRootQueueDisc("ns3::FifoQueueDisc", "MaxSize", QueueSizeValue(queueSize));

    // 應用程序的創建和配置
    UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(20));

    std::vector<int> packet_count = {2000, 200, 200, 200, 200, 200, 200, 200, 200, 200}; // packet大小以及數量
    for (std::vector<int>::size_type i = 0 ; i < packet_count.size(); ++i) {
        uint32_t packetSize = packet_count[i];
        Ptr<ns3::Packet> packet = Create<ns3::Packet>(packetSize);
        echoClient.SetAttribute("PacketSize", UintegerValue(packet->GetSize()));
        ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
        clientApps.Start(Seconds(2.0 + i*10));
        clientApps.Stop(Seconds(2.0 + i*10 + 2.0)); 
    }

//-----------------------------------------------------------------------------------------------------------------------------------
//以下請勿更動 以下請勿更動 以下請勿更動 以下請勿更動 以下請勿更動 以下請勿更動 以下請勿更動 以下請勿更動 以下請勿更動 以下請勿更動 以下請勿更動 
//-----------------------------------------------------------------------------------------------------------------------------------
    
	//流量監控
	Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();
    Simulator::Stop (Seconds (1200.0));
	//運行模擬
    Simulator::Run();
    flowMonitor->CheckForLostPackets();
    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowHelper.GetClassifier());
    std::map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats();
    FlowMonitor::FlowStats totalStats;
    totalStats.txPackets = 0;
    totalStats.rxPackets = 0;
    totalStats.lostPackets = 0;
    totalStats.rxBytes = 0;
    double totaldelaySum = 0;
    for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator it = stats.begin(); it != stats.end(); ++it) {
        double delayInNanoSeconds = it->second.delaySum.GetNanoSeconds() / 1.0e6;
        totalStats.txPackets += it->second.txPackets;
        totalStats.rxPackets += it->second.rxPackets;
        totalStats.lostPackets += it->second.lostPackets;
        totalStats.rxBytes += it->second.rxBytes;
        totaldelaySum += delayInNanoSeconds;
    }
    std::cout << "總體統計信息：\n";
    std::cout << "  Tx Packets: " << totalStats.txPackets << "\n";
    std::cout << "  Rx Packets: " << totalStats.rxPackets << "\n";
    std::cout << "  Lost Packets: " << totalStats.lostPackets << "\n";
    std::cout << "  Delay: " << totaldelaySum << " ms\n";
    Simulator::Destroy();
    return 0;
}
