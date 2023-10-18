Introduction & Review of cellular networks
===
🔙 [MENU README](../README.md)


# Trends of Mobile Traffic
CISCO Global Nobile Data Traffic Growth
![](../src/CISCO%20Mobile%20Data%20Traffic%20Growth.png)
 > Note: 1 exabyte (EB)=1000^6 bytes=10^18 bytes

1. Now is 49EB(Extrabytes per Month)
    > Observation: We need new technologies to support the upcoming mobile traffics
2. **LTE-A(Standard 4G)**: peak downlink 1 Gbps, peak uplink 500Mbps
3. **5G** is designed to deliver **peak data rates up to 20 Gbps** based on IMT-2020 requirements
    > IMT-2020 : International Mobile Telecommunications-2020 (IMT-2020 Standard) proposed by ITU (International Telecommnuication Union) in 2015
    - However, one prerequisite for achieving 1Gbps speeds with 5G is that the device needs to be located **near a base station**.
    - 光寶's product, the small base station, has a coverage range of 20 meters
    - The development of 5G is moving towards high-density, low-power, multi-antenna, and highly directional solutions.
3. WiFi is getting important
![](../src/Traffic%20from%20Mobile%20Devices.png)
The reasons why Wi-Fi is becoming increasingly important are: **Cost issue** 、 **Coverage issue**

> We can see that the usage of Wi-Fi has exponentially increased. 

> "Cellular traffic" refers to data or communication traffic carried over cellular networks, such as 2G, 3G, 4G, or 5G networks. => mobile device

> "Offload traffic" refers to the process of diverting or transferring network traffic from one network or interface to another, often to relieve congestion or optimize network performance. This can include moving traffic from cellular networks to Wi-Fi networks, for example. => wifi

5. **Heterogeneous network**
- Heterogeneous network
  - A heterogeneous network (HetNet) combines various technologies and communication methods within a single network. 
  - It's used in modern communications, including 2G, 3G, 4G, 5G, Wi-Fi, and more,to improve coverage and performance, especially for smartphones, IoT, and data transmission.
- Future
  - Wi-Fi also faces some regional or coverage-related issues, such as instability during mobility. 
  - The future of networking is undoubtedly moving towards a heterogeneous network, including low Earth orbit satellite communication.
  - **The development of a single network type is not what we look forward to.**

---

# Device Analysis
1. Cisco, Ericsson, TI, and others predict there will be more than 20 billions connected devices by 2020
2. Bringing connectivity to those objects is challenge

![](../src/Global%20Device%20Connection%20Growth%20by%20Type.png)
> M2M is about Internet of Things (IoT) devices.

> Smart manufacturing, intelligent transportation, telemedicine, smart homes, and automotive autonomous driving devices all fall under the category of IoT devices.


---

# Application Traffic Growth
![](./../src/Application%20Traffic%20Growth.png)
> Videos encompass not only entertainment but also remote work, real-time surgeries, video conferences, and internet surveillance, and more.


---

# New Technology Development Trends
1. Not only **Small cell**,but also high-density, low-power, multi-antenna, and highly directional solutions.
2. Multi-RAN (heterogeneous network)
3. Unlicensed band utilization [LTE-U: LTE-LAA (License Assisted Access)] is defined by the **3GPP organization**.
    > Using Wi-Fi in areas with limited or no cellular traffic coverage.
  - LTE-U enables LTE signals to work in unlicensed spectrum bands to enhance wireless network performance
  - LTE-LAA combines licensed and unlicensed spectrum to improve network capacity and efficiency.
    

    ![](../src/New%20Technology%20Development%20Trends.png)


4. Cloud/edge computing
   - Expansion of Resources and Computing Capacity
5. SDN & NFV
   - **Software-Defined Networking** : is a network architecture that separates network control and data forwarding functions,and managed by central controller software allowing for more flexibility and programmability in managing network configurations.
   - **Network Function Virtualization** : is a method of virtualizing network infrastructure components, such as routers and firewalls, to replace traditional hardware devices with virtualized software instances, enhancing network scalability and efficiency.
6. Network slicing
   - Resource slicing : Bandwidth、port、cpu、Antenna
   - For the sake of transmission speed,QoS and special channels.
   - Challenges of E2E Network Slicing: Crossing WANs, Different Manufacturers and Devices, Various Owners, Dynamic Allocation, and **Real-time** Requirements.
7. Service-oriented cloud
   - Scalable and flexible, no longer requiring the construction of large data centers.
8. Internet QoS
   - Professionals:Measure traffic, latency, and network quality.
   - General users:Survey rating to assess user experience and integrating **machine learning** for future network architecture model evaluation.
9. Resource management
10. Massive MIMO
    - Multiple antennas.
    - The higher the frequency, the smaller the antenna size. This is why older mobile phones used to have a large antenna, while modern ones no longer visibly feature an antenna.
    - The higher the frequency, the smaller the antenna size, making it possible to create array antennas within devices.
    - MIMO (Multiple Input, Multiple Output)performs **channel detection and precoding mathematical calculations** to avoid interference between multiple antennas.
    - If the calculation results are **in polar coordinates and orthogonal**, they do not affect each other.
    - However, because channel detection and state feedback also take time, the benefits of MIMO, which originally increase speed, will be reduced. Therefore, **there exists an optimal value for the trade-off between the number of antennas and speed.**
11. CoMP (Coordinated Multi-Point Transmission)
    - Cooperative transmission **between different base stations and different access points**.
    - It aims to reduce interference, enhance transmission speeds, expand coverage areas, and thus improve the quality and efficiency of wireless communication. This is particularly useful in high-density user areas and edge coverage zones.
12. Beamforming technology
    - Transmitting and receiving wireless signals in a specific direction or towards specific devices to enhance signal strength, reduce interference, and increase data transmission rates.
    - For example,Omnidirectional propagation can lead to a problem where energy is wasted when individuals who are not intended recipients also receive the signal in the forward direction.





















































