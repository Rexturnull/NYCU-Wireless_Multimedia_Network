Introduction to Quality of Service
===
🔙 [MENU README](../README.md)

In the early days of the Internet, we didn't pay much attention to service quality; it was primarily used for text-based communication. As it evolved, we introduced elements like voice and video, and that's when we started experimenting with adding features to the Internet. This meant introducing **new protocols** without altering the fundamental design of TCP/IP. 
However, since these protocols were not mandatory, not all computer devices supported the newly introduced protocols

---

# Quality of Service
1. Two main objectives
   - Provide performance assurance in the managed network
     **Performance assurance** is dynamically adjustable but must be **based on an average data**, for example, 1MHz per second or latency time.
   - Support service differentiation among users/flows
     For example,Remote Surgery
2. Formal definition of QoS
   - The capability to provide resource assurance and service 
differentiation in a network is often referred to as quality of service
3. How to provide QoS?
   - Resource allocation mechanism (i.e., user/resource scheduling)
   - Proper definition of the adopted QoS index


![](../src/Quality%20of%20Service.png)
> - ITU-T : International Telecommunication Union Telecommunication Standardization Sector
> - QoS class 5 is best effort
> - U : Undefined

![](../src/Quality%20of%20Service%202.png)
> QoS in 5G


![](../src/Quality%20of%20Service%203.png)
> The delay of each packet minus the square of the average, divided by the average delay.

---

# Resource Allocation
1. The process that network elements perform to 
meet the demands of users/applications
2. What are the mentioned **resources**?
   - **Bandwidth** of the links
     Packets at a router/switch contend for the use of links
   - **Buffers** at the routers and switches
     These contending packets are placed in queues to wait for been 
transmitted over the links
   - CPU (hard to control)

# Congestion Control
1. Allocating resources with any precision is difficult, 
since resources are distributed throughout the 
network
2. When too many packets are contending for the same link
   - The queue overflows, and thus packets get dropped
   - Packet drop triggers retransmissions
   - Also packet drop is a sign of network congestion
3. Network should provide a congestion control mechanism to deal with such a situation
    >  We need to select the packet source with the **highest content in the queue or buffer** for traffic control .
    > Or **appropriate dropping of packets**, allowing the entire link to be relieved **before reaching a critical threshold**.
4. Strategy of **traditional** Internet
   - Always let the sources send as much data as they want
   - Then recover from the congestion when it occurs
   - Easier approach but it can be disruptive because many packets many be discarded by the network before congestions can be controlled
5. Better cooperation
   - **In network elements**
    Various **queuing** disciplines can be used to control the order in **which packets get transmitted and which packets get dropped**.
   - **At the hosts’ end**
    The congestion control mechanism paces how fast sources are allowed to send packets



---

# Classification of Resource Allocation
1. Router-centric v.s. host-centric
   - Router-centric: **router is responsible for deciding** when packets are sent and selecting which packets are to be dropped, and informing the hosts that how many packets they are allowed to send as well
   - Host-centric: end host **observes the network conditions** and 
adjusts its behavior accordingly
   - <font color="red">These two are not mutually exclusive</font>
2. Reservation-based v.s. feedback-based
   - Reservation-based: end host asks the network for a certain 
amount of **capacity to be allocated for a flow**.
   - Feedback-based: end host begins sending data **without reserving 
any capacity** and then **adjusts** its sending rate according to the 
received feedback. Feedback could be “explicit” or “implicit”
        > "**explicit**" typically requires **additional control packets**
3. Window-based v.s. rate-based
   - Window-based: the well-known one is **TCP**, in which the receiver 
advertises a window to the sender. This window limits how much 
data the sender can transmit
   - Rate-based: **how many bits per second** a sender can send is 
controlled so that the receiver or network can absorb. Rate-based 
control makes sense for multimedia applications


00:55:00