Integrated Service
===
🔙 [MENU README](../README.md)

# Motivation of IntServ
1. **IP network does not support QoS.** Characteristics of IP network include:
   - Best effort service only (**Non-existent error-checking and retransmission mechanism**)
   - Fair access to all(**without any priority**)
   - FIFO queueing discipline(Fair access)
   - **Window-based congestion control**(Network congestion control algorithm used in TCP,**The window size represents the number of data packets the sender can transmit without waiting for acknowledgments**)
2. The goal of IntServ is to **preserve the datagram model of IP-based networks and support resource reservation for real-time application**
3. The basic approach of IntServ is **<font color=red>per-flow resource reservation**</font>
4. An implicit assumption of resource reservation is that **the demand for bandwidth still exceeds supply**,**If the demand for bandwidth is less than the supply, resource reservation is not needed.**
5. The IntServ architecture assumes that the main quality of service about which **the network makes commitments is the per-packet delay** (in fact, the worst-case delay bound)

---

# Key Components of IntServ
![](../src/Key%20Components%20of%20IntServ.png)

> Resource reservation table is similar to a routing table + Reservation Resource.



1. The reference model defines two phases logically
   - **Control phase: set up resource reservation**
     - **<font color=red>Addmission control</font>**
   - **Data phase: forward data packets based on the reservation state**
2. InServ provides **3** traffic classes
   - Guaranteed service
   - **Controlled load service**
   - Best-effort

---

# How to Setup Resource Reservation in IntServ
1. Step 1: **Flow specification**
   - An application characterizes its traffic flow and specifies the QoS requirements
2. Step 2: **Route selection**
   - The reservation setup request is sent to the network (routers)
   - Router interacts with routing module to **determine the next hop to which the reservation request should be forwarded**
   - The router also coordinate with the **admission control to decide whether there are sufficient resources to meet the requested resources**
   - Once the reservation setup is successful, the information for the **reserved flow is installed into the resource reservation table**
   - The information in the resource reservation is then **used to configure the flow identification module and the packet scheduling module in the data plane**

## Flow Specification
1. Essentially a **<font color=red>service contract</font>** Common parameters
   - **Peak rate** : The highest rate at which a source can generate traffic
   - **Average rate** : The average transmission rate over a time interval
   - **Burst size** : The maximum amount of data that can be injected into the network at the peak rate
2. In Integrated Services, **the admitted flow rate is implemented by means of <font color=red>token bucket</font>**
3. A **<font color=red>token bucket</font>** is with two parameters(In Router)
![](./src/../../src/token%20bucket.png)
> - Token arrival rate r and bucket depth b
> - Tokens drop into the bucket at a constant rate r
> - Tokens are consumed by the incoming packets
> - When a packet arrives, the regulator will send this packet only if the bucket has enough tokens
> - When a packet leaves the token bucket, the regulator removes the amount of tokens equal to the size of the outgoing packet
> - The depth b is the limit on the maximum amount of tokens that can be accumulated

---

# Challenges of Route Selection
1. Currently protocols typically use a simple metric, such as delay, hop count, or administrative weight to **<font color=red>compute the shortest paths</font>** to all destination networks 
→ **lacks of necessary information about the available resources to make an intelligent decision**
2. This issue is further complicated by the fact that applications may have multiple requirements → NP complete problem
3. Many interesting schemes have been proposed to resolve this problem, but none have been implemented in commercial products
4. Therefore, **<font color=red>IntServ decouples routing from the reservationprocess, and assumes the routing module in a router will supply the next hop**</font>

---

# More About Reservation Setup
1. We need a protocol to carry the information about traffic characterization and resource requirements so that each router along the path can determine to accept or deny the request
2. We also need a reservation setup protocol that goes hop by hop along the path to install the reservation state in the routers
3. The reservation setup protocol must deal with changes in the network topology
4. In IntServ, **<font color=red>RSVP (ReSerVation Protocol)</font>** is the adopted reservation setup protocol 
5. Features of RSVP
   - A **<font color=red>receiver-initiated approach</font>** and is designed to work with IP multicast
   - Allows different reservation styles
   - **Soft-state approach** to deal with resource changes : **Periodic notifications** are needed to indicate whether the data is retained in the buffer.


# Admission Control
1. Two functions of admission control
   - Determine **<font color=red>if a new reservation can be setup</font>** based on the admission control policy
   - **<font color=red>Monitor and measure the available resources</font>**
2. Two basic approaches to admission control
   - **Parameters based**
     - **A set of parameters is used to precisely haracterize traffic flows**
     - **Difficult to give accurate**, tight traffic models
   - **Measurement based**
     - The network **measures the actual traffic load** and uses that for admission control
3. Most common used methods
   - **Simple sum**: the sum of requested bandwidth for all current flows and the new flow **does not exceed the link capacity**. This is the most conservative approach
   - **Measured sum**: the measured sum approach uses the measured **<font color=red>load of existing flows</font> rather than the bandwidth requested by them**
   - **Acceptance region**: **maximize the reward of utilization increases against packet losses.** 
   Given the statistical models of traffic sources, the acceptance region for a type of traffic can be
    ![](./src/../../src/Admission%20Control%20-%20Acceptance%20region.png)
   - **Equivalent bandwidth**: the equivalent bandwidth for a set of flows is defined as the bandwidth C(p) such that the stationary bandwidth requirement of the set of flows exceeds this value with a probability of at most p (**Based on probabilistic models.**)
4. How to measure the traffic load of existing flows?
   - **Exponential averaging over consecutive measurement**:
   ```math
   NewEstimation = (1-w) * OldEstimation + w * NewMeasurement
   ```
   - Time window: the average arrival rate is measured over a sampling interval. At the end of a measurement period the **highest average is used as the estimated rate**. Suppose there are n sample intervals in a measurement period T and **Ci is the average rate measured over sampling interval i**; then
   ```math
   EstimationRate = max[C_1,C_2,...C_n]
   ```
---

# Flow Identification
1. In packet processing a router must examine every incoming packet and decide **if the packet belongs to one of the received RSVP flows**
2. The task is performed at packet classifier (**inside a router** actually)
3. Each packet is identified by five fields (five-tuple) in the packet header
<font color=red>
   - Source IP address
   - Destination IP address
   - Protocol ID
   - Source port
   - Destination port

</font>

---

# Packet Scheduling
1. Packet scheduling is responsible for enforcing resource 
allocation
2. Common scheduling methods
<font color=red>
   - Fair queueing: WFQ
   - Deadline-based: EDF
   - Rate-based: virtual clock (timestamp)

</font>

---

# Service Models Defined in IntServ
## Guarantee service
1. **Provided guarantee bandwidth and strict** bounds on **end-to-end queueing delay (max)** for conforming flows
2. The end-to-end behavior of a path that supports guaranteed service can be **viewed as a virtual circuit (more flexible than real circuit) with <font color=red>guaranteed bandwidth</font>**
3. **TSpec** (traffic specification)
   - Bucket rate r (bytes/second): the rate at which tokens arrive at the token bucket
   - Peak rate p (bytes/second): the max rate at which packets can transmit
   - Bucket depth b (bytes): the size of the token bucket
   - Min policed unit m (bytes): any packet with a size smaller than m will be counted as m bytes
   - Max packet size M (bytes): the max packet size that can be accepted
1. **RSpec** (service specification)
   - **Service rate R** (bytes/second): the **bandwidth requirement**
   - **Slack term S** (microseconds): the **extra amount of delay** that a node may add that still meets the end-to-end delay requirement
2. Delay calculation
   - **Best-case end-to-end queueing delay**: **<font color=red>b/R (p → infinity, R >= r)</font>**
   - **Worst-case end-to-end queueing delay**: **<font color=red>b/R + (p - r)/R (p > R >= r)</font>**
   - Check the definition of b, p, R and r
     - b (token bucket size): The size of the token bucket determines the flow's burst traffic capability.
     - p (peak rate): The peak rate refers to the maximum rate that the flow can achieve in a short period.
     - R (service rate): The service rate is the bandwidth guaranteed by the network for the flow.
     -  r (reserved rate): The reserved rate is the minimum bandwidth that the flow can use at any time.







## Controlled-load service
1. Emulate a **lightly loaded network** for applications that request this service
2. **More efficient than guarantee service** by allowing statistical multiplexing
3. Well fit with adaptive applications that require some degree of performance assurance but not absolute bounds 
4. A service model between the best effort and guaranteed service through appropriate admission control and traffic isolation mechanisms (**better-than-best-effort service**)
5. End-to-end behavior
   - Very high probability that transmitted packets are successfully delivered to the destination
   -  **End-to-end transit delay measured for a very high percentage of packets not greatly exceeding the <font color=red>min end-to-end transit delay</font>**
6. The acceptance of a request for the controlled load service implies that the network has sufficient resources to accommodate the **traffic without causing congestion**
7. **TSpec** is allowed to specify this desired traffic parameters
8. New request can be accepted only when all nodes over the path have sufficient resources available to accommodate the new flow
9. Admission control is left as a local matter
10. **<font color=red>Traffic policing**</font>
    - When non-conformant packets arrive, the network must continue to **provide the contracted service guarantees to conforming flows**
    - The network should prevent the excessive controlled load traffic from **unfairly impacting the best-effort traffic**
    - The network must attempt to deliver the excessive traffic when it can do so without violating the previous two requirement


# RSVP
1. ReSerVation Protocol [RFC 2205]
2. RSVP is used
   - by **<font color=red>hosts to communicate service requirement to the network**</font>, and
   - by **<font color=red>routers**</font> in the network **<font color=red>to establish a reservation state along a path**</font>
3. RSVP is 
   - **not** a routing protocol
   - **not** providing network services
   - **not** the only IP reservation protocol
## Two key concepts: flow and reservation
1. Flow
   - **Traffic streams from a sender to one or more receivers**
   -  **Flowspec** describes both the characteristics of the **traffic stream sent by the source and the QoS the flow requires**
   - Workable for **unicast** and **multicast** flows
2. Reservation
   - Simplex reservation: RSVP **makes a reservation in only one direction**
   -  **<font color=red>Receiver-initiated</font>**: to accommodate heterogeneous anddynamic receivers in a multicast group
   -  **Routing independent**: RSVP process consults the forwarding table (**constructed by the routing protocol**) and sends the RSVP messages accordingly
   -  **Policy independent**: RSVP provides a general mechanism for creating and maintaining a reservation state over a multicast tree or a unicast path; **the control parameters carried in the RSVP message are opaque from the RSVP perspective**
   - **Soft state**: to support dynamic membership and network topology changes by **setting a timer for each reservation state**
   - **Reservation style**: to specify how reservation for the same multicast group should be aggregated at the immediate routers

## Two major messages of RSVP
![](./src/../../src/RSVP%20message.png)
1. Path message
   - **Generated by the sender**
   - **Travel in the routing direction**, determined by unicast or multicast routing protocols 
   - **Purposes**
     - **Distributing source info to receivers**
     - **Passing on path’s characteristics**
     - **Providing info for receivers** to reach senders
   - **Path spec**
     - Flow ID (sender Template): sender IP address and optionally the UDP/TCP sender port
     - Flowspec (i.e., sender TSpec, not modified by the intermediate nodes)
     - **Adspec**: **optional element** in the PATH messages that is used to carry the OPWA (One Pass with Advertising). Adspec is passed to the local traffic control at each node,which returns an updated Adspec and then is forwarded in PATH messages sent downstream
   - **PHop (Previous Hop)**
2. Reservation message
   - **Generated by the receiver**
   - Travel in the **reverse direction** of Path message
   - **RESV spec**
     - Flowspec: specifies the desired QoS and parameters to be used in packet scheduling
     - Reservation style
     - **NHop(Next Hop)**
   - **Merging reservation requests whenever possible**

## RSVP operation
1. If Path state and Resv state exist,
   - Path messages and Resv messages are sent by sender and receiver, respectively, **periodically to refresh existing states**
2. Otherwise,
   - Sender sends a Path message first to set up the Path state in the routers, and then receivers send Resv requests in the reverse direction
3. **Admission control** and **policy control**
4. RSVP is an **one pass reservation model**(Cannot negotiate)
5. An enhancement is one pass with **advertising** (OPWA)

## Packet filtering
1. A separate function from resource reservation
2. A function which selects those packets that can use the reserved resources
3. Each packet is identified by five fields (five-tuple) in the packet header

## Reservation style: 
- how **multiple requests are merged** and which resource requests are forwarded to the upstream node
- **Fixed filter (FF)**
  - Explicit sender selection + **distinction reservation**
  - E.g., FF(S1{Q1}, S2{Q2},.., Sn{Qn}), where Q1, Q2, .., Qn are corresponding flowspecs, and S1, S2, .., Sn are senders
   ![](./src/../../src/Fixed%20filter.png)


- **Wildcard filter (WF)**
  - Wildcard sender selection + **shared reservation**
  -  All receivers share a single reservation whose **<font color=red>size is the largest of the resource requests</font>**
  - **All upstream senders can use the reservation**
  - E.g., WF(*, {Q}), where Q is the flowspec, * represents the wild-card sender selection
   ![](../src/Wildcard%20filter.png)

- **Shared explicit (SE)**
  - Explicit sender selection + **shared reservation**
  - E.g., SE((S1, S2, S4{Q}), where Q is the flowspec, and S1, S2, S3, S4 are senders
   ![](./src/../../src/Shared%20explicit.png)


- Shared reservation (WF and SE) are **designed for multicast applications**
  - Typically only one or two people can speak at the same time in
audio conferencing. An WF or SE reservation request for twice the bandwidth for one sender should be sufficient in such cases

## Explicit vs. wildcard server selection
- **Explicit**: the reservation made only for senders explicitly listed in the RESV message
- **Wildcard**: for any sender

## Distinct vs. shared reservation
- **Distinct**: each sender has its own RSVP flow
- **Shared**: using the same RSVP flow for multiple senders

# Disadvantages of IntServ
- When IP flow is terminated, the resources are not immediately released
- **Lack of scalability**
- **Refreshing signaling is bandwidth consuming**


# More About Adspec
1. This object is modified by an intermediate node, pass 
information to the next hop, and finally the receiver can 
determine the characteristics of the end-to-end path
2. Adspec object has 3 components
   - **Default general parameters fragment**, which contains
     - Minimum path latency
     - Path bandwidth
     - Integrated Services hop count: the total umber of hops that are capable of support the Integrated Services
     - Global break bit: 0 set by the sender. **If any node along the path does not support Integrated Services, the bit is set to 1 and the information is passed on to the receiver**
     - **Path MTU:** the maximum transmission unit of the path
   - **Guaranteed service fragment, which contains**
     - Ctot: the sum of **rate-dependent delay** (rate & packet length) over a path
     - Dtot: the sum of **rate-independent delay** (e.g., router pipeline delay) over a path
     - Csum: partial sum of C between shaping points
     - Dsum: partial sum of D between shaping points
   - **Controlled load service fragment: no extra data in the Adspec**


# One Pass v.s. One Pass with Advertising (OPWA)
1. **One pass model does not support the capability of determining the characteristics of the path or whether the path is able to support the desired QoS**
2. With **OPWA**, the sender **includes an Adspec in its <font color=red>PATH message</font>** to collect the information about the path

# Slack Term
1. For guaranteed service, there is a “Slack term” field in the 
RSpec in an RSVP message
2. Assume a flow needs 2.5 Mbps bandwidth
3. Slack term is utilized to compensate the increased delay
4. Slack term is the difference between the desired delay and 
the actual delay obtained with current bandwidth reservation (i.e., delay credit)

![](./src/../../src/slack%20team.png)