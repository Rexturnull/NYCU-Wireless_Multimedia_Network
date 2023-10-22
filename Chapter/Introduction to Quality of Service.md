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
## Resource Allocation
1. The process that network elements perform to meet the demands of users/applications
2. What are the mentioned **resources**?
   - **Bandwidth** of the links
     Packets at a router/switch contend for the use of links
   - **Buffers** at the routers and switches
     These contending packets are placed in queues to wait for been 
transmitted over the links
   - CPU (hard to control)

## Congestion Control
1. Allocating resources with any precision is difficult,since resources are distributed throughout the network
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



## Classification of Resource Allocation
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

---

# Evaluation Criteria

## Delay
1. **Queueing Delay**: When a packet arrives at a router or switch, and other packets are already waiting for transmission, it must wait in a queue for forwarding. This queueing delay depends on network congestion levels and the queuing algorithms in use.
2. **Processing Delay**: At routers or switches, packets require processing, such as routing decisions and MAC address lookup. This processing delay is influenced by device performance and workload.
3. **Transmission Delay**: This is the time required for a packet to traverse the physical media, typically related to bandwidth and packet size. Larger packets or lower bandwidth can increase transmission delay.
4. **Propagation Delay**: It is the time required for a packet to travel from the sender to the receiver, typically determined by physical distance and the signal propagation speed of the transmission medium. Propagation delay is an inherent physical delay.
5. **Queuing Jitter Delay**: This is the irregularity in queuing delay caused by variations in network congestion and queuing algorithms. It may lead to inconsistent transmission times between packets.
6. **Retransmission Delay**: When a packet is lost or damaged during transmission and needs to be resent, it introduces additional delay. This is typically associated with error recovery mechanisms within the network.

## Effectively
- How to evaluate the **effectiveness** of the adopted resource 
allocation?
  - Through **throughput and delay** performance
  - **<font color="red">However, throughput and delay conflict with each other</font>**
  - We want send as many packets into the network as possible to 
drive the utilization of all links up to 100%
  - While this would result in increasing the number of queued 
packets in the network; and thus the queue length and queueing 
delay increase as well
- **<font color="red"> Criteria : Ratio of Throughput to Delay </font>**
  1. One common metric to evaluate the effectiveness of a resource allocation scheme is the ratio of throughput to delay
   ![](../src/ratio%20of%20throughput%20to%20delay.png)
  2. The objective is to **maximize** this ratio
  3. A representative power curve is shown below,The power curve looks very much like the system throughput curve in a timesharing computer system
   ![](../src/Powert%20Curve.png)


## Fairness
- How to evaluate the **fairness** of a resource allocation?
  - Fairness means that each flow receives an **equal share of the bandwidth**
  - However,**<font color=red>equal shares may not equate to fair shares</font>**
   > Locally fair share v.s. globally fair share 
   > of the three flows in the illustrative example below

   ![](../src/fair%20share.png)

- **<font color="red">Criteria : Jain’s fairness index</font>**
  1. Given a set of flow throughputs , the fairness index to these flows is
  ![](../src/Jain's%20fairness%20index.png)
  2. The fairness index always results in a number between 0 and 1, **with 1 representing the greatest fairness**. Consider n flows, each one receives a throughput of 1 unit of data per second, therefore the fairness index is
   ![](../src/fairness%20index.png)
  3. Suppose one flow receives a throughput of 1+X. Now the fairness 
index is
   ![](../src/throughput%20of%201+X.png)
  4. To **add weights to the Jain fairness index**, you can modify the formula as follows
      ```math
      J weighted = (Σ(wi * Ri)^2) / (n * (Σwi * Ri)^2)
      ```
      > In your case, you want to add weights of 1.5, 3.5, and 1 to three different users. Let's assume the users are labeled as User 1, User 2, and User 3, and their respective allocations are R1, R2, and R3. Here's how you can calculate the weighted Jain fairness index:

      ```math
      Jweighted = [(1.5 * R1)^2 + (3.5 * R2)^2 + (1 * R3)^2] / [n * (1.5 * R1 + 3.5 * R2 + 1 * R3)^2]
      ```

---

# Queueing Disciplines
## Queueing Disciplines
1. Method implemented in routers to govern how packets are 
buffered while waiting to be transmitted
2. Queueing algorithm can be thought of as allocating both 
**bandwidth** (which packets get transmitted) and **buffer space** (which packet get discarded)
3. Queueing algorithm directly **affects the latency experienced by a packet by determining how long a packet waits to be transmitted**
4. Two common queueing algorithms are first-in first-out 
(**FIFO**) and fair queueing (**FQ**)

## FIFO
1. The first packet that arrives at a router is the first packet to be transmitted <font color="red">without priority</font>
2. Packets that arrives at the tail end of the FIFO are dropped (**tail drop**)
3. **Regardless of which flow the packet belongs to or how important the packet is**
4. Note that scheduling discipline differs from drop policy
5. **<font color="red">Drop policies typically involve how to select packets for discarding, while queueing disciplines primarily concern the scheduling order of packets.</font>**

![](../src/FIFO%20Queue.png)

## Priority Queueing
1. A variation on basic FIFO is priority queueing
2. Idea
   - **Each packet is with a priority**
   - Router implements **multiple FIFO queues**, one for each priority class
   -  Router **always transmits packets out of the highest-priority queue** if the queue is nonempty before moving on to the next priority queue
   - Within each priority, packets are still managed in a FIFO manner
3. Problem of priority queueing: **high priority queue can starve out all the other queues**
   To solve this problem : we will **allocate a mininum service rate to lower-priority queues**, ensuring they receive some share of the service capacity.

## Fair Queueing
1. Main problem with FIFO queuing: it does not discriminate between different traffic sources, or it 
does not separate packets according to the flow to 
which they belong.Fair queuing (FQ) is to address this problem.
2. Idea
   - Router maintains a **separate queue for each flow** currently being handled by the router
   - The router then serves these queues **in a sort of round robin**
   - For each flow, there is a corresponding queue.

![](../src/Fair%20Queue.png)

3. Problem : 
   -  the packets being processed at a router are **<font color=red>not necessarily the same length**</font>, it is necessary to take packet length into consideration.
   -  For example, if a router is managing two flows, 
      one with 1000-byte packets 
      and the other with 500-byte packets, 
      then a simple round-robin servicing of packets from each flow’s queue 
      will give the first flow 2/3 of the link’s bandwidth and 
      the second flow only 1/3 of its bandwidth
4. We really want is bit-by-bit round-robiny,but it is not feasible to interleave the bits from different packets
5. The FQ mechanism therefore simulates this behavior by **first determining when a given packet would finish being transmitted** if it were being sent using bit-by-bit round-robin,and then **using this finishing time to sequence the packets for transmission**
   <font color=red>
   - Pi: the length of packet i
   - Si: time when the router starts to transmit packet i
   - Fi: time when router finishes transmitting packet i
   - Fi = Si + Pi

   </font>

   **Packets are transmitted in order of increasing Fi values.**
5. When do we start transmitting packet i
   - Depends on whether packet i arrived before or after the router 
finishes transmitting packet i-1 for the flow
   - Let Ai denote the time that packet i arrives at the router
   - Then Si = max(Fi-1, Ai)
   -  Fi = max(Fi-1, Ai) + Pi
   -  Now for every flow, we calculate Fi for each packet that arrives using our formula
   -  We then treat all the Fias timestamps
   -  Next packet to be transmitted is always the packet that has the lowest finish timestamp

![](./src/../../src/Fair%20Queue%20transmitting%20packet%20i.png)

6. Two notes of fair queueing
   - **When a flow is empty, it will be skipped**.The link is never idle as long as there is at least one packet in the queue (we call this **work conserving**)
   - If the link is fully loaded and there are n flows sending data, **one cannot use more than 1/n** of the link bandwidth
   - If one tries to send more than that, it itself would incur long delay

7. **Weighted fair queueing (WFQ)**
   - Each flow (queue) is assigned a weight
   - This weight logically specifies how many bits to transmit each time the router serves that queue
     **Example, weight:2 ,P / 2 to reduce the value of Fi and increase its transmission priority.**
   - Therefore, this weight controls the percentage of the link’s bandwidth that the flow will get


# Proportional-Fair Resource Allocation
1. Motivation of proportional fairness : **Maximize the total wireless network throughput** while at the same time allowing all users **at least a minimal level of service**
2. Formal definition
   - let T be the observation time duration
   - Let Ti be the time utilized by flow i
   - Let Ri be the data rate of flow i
   - The throughput of flow i is Si=(TiRi)/T
   - Proportional fairness is to achieve ![](../src/Proportional%20fairness.png)
   - U(•) is utility function,The common utility function is log,between **0~1**

