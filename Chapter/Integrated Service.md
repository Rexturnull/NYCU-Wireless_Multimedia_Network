Integrated Service
===
🔙 [MENU README](../README.md)

# IntServ
1. Motivation of IntServ
   - **IP network does not support QoS.**Characteristics of IP network include:
   - Best effort service only (**Non-existent error-checking and retransmission mechanism**)
   - Fair access to all(**without any priority**)
   - FIFO queueing discipline(Fair access)
   - Window-based congestion control(Network congestion control algorithm used in TCP,**The window size represents the number of data packets the sender can transmit without waiting for acknowledgments**)
2. The goal of IntServ is to **preserve the datagram model of IP-based networks** and support resource reservation for real-time application
3. The basic approach of IntServ is **<font color=red>per-flow resource reservation**</font>
4. An implicit assumption of resource reservation is that **the demand for bandwidth still exceeds supply**,**If the demand for bandwidth is less than the supply, resource reservation is not needed.**
5. The IntServ architecture assumes that the main quality of service about which **the network makes commitments is the per-packet delay** (in fact, the worst-case delay bound)

# Key Components of IntServ
![](../src/Key%20Components%20of%20IntServ.png)

> Resource reservation table is similar to a routing table + Reservation Resource.



1. The reference model defines two phases logically
   - **Control phase: set up resource reservation**
     - <font color=red>Addmission control</font>
   - **Data phase: forward data packets based on the reservation state**
2. InServ provides 3 traffic classes
   - Guaranteed service
   - **Controlled load service**
   - Best-effort

---
# How to Setup Resource Reservation in IntServ
1. Step 1: Flow specification
   - An application characterizes its traffic flow and specifies the QoS requirements
2. Step 2: Route selection
   -  The reservation setup request is sent to the network (routers)
   -  Router interacts with routing module to determine the next hop to which the reservation request should be forwarded
   - The router also coordinate with the admission control to decide whether there are sufficient resources to meet the requested resources
   - Once the reservation setup is successful, the information for the reserved flow is installed into the resource reservation table
   - The information in the resource reservation is then used to configure the flow identification module and the packet scheduling module in the data plane

## Flow Specification
1. Essentially a **<font color=red>service contract</font>** Common parameters
   - **Peak rate** : The highest rate at which a source can generate traffic
   - **Average rate** : The average transmission rate over a time interval
   - **Burst size** : The maximum amount of data that can be injected into the network at the peak rate
2. In Integrated Services, **the admitted flow rate is implemented by means of token bucket**
3. A **<font color=red>token bucket</font>** is with two parameters(In Router)
![](./src/../../src/token%20bucket.png)
> - Token arrival rate r and bucket depth b
> - Tokens drop into the bucket at a constant rate r
> - Tokens are consumed by the incoming packets
> - When a packet arrives, the regulator will send this packet only if the bucket has enough tokens
> - When a packet leaves the token bucket, the regulator removes the amount of tokens equal to the size of the outgoing packet
> - The depth b is the limit on the maximum amount of tokens that 
can be accumulated

# Challenges of Route Selection
1. Currently protocols typically use a simple metric, such as delay, hop count, or administrative weight to **<font color=red>compute the shortest paths</font>** to all destination networks → **lacks of necessary information about the available resources to make an intelligent decision**
2. This issue is further complicated by the fact that applications may have multiple requirements → NP complete problem
3. Many interesting schemes have been proposed to resolve this problem, but none have been implemented in commercial 
products
4. Therefore, **<font color=red>IntServ decouples routing from the reservationprocess, and assumes the routing module in a router will supply the next hop**</font>

---

# More About Reservation Setup
1. We need a protocol to carry the information about traffic
characterization and resource requirements so that each router along the path can determine to accept or deny the request
2. We also need a reservation setup protocol that goes hop by hop along the path to install the reservation state in the routers
3. The reservation setup protocol must deal with changes in the network topology
4. In IntServ, **RSVP (ReSerVation Protocol)** is the adopted 
reservation setup protocol 
5. Features of RSVP
<font color=red>
   - A receiver-initiated approach and is designed to work with IP multicast
   - Allows different reservation styles
   - Soft-state approach to deal with resource changes : Periodic notifications are needed to indicate whether the data is retained in the buffer.

</font>

# Admission Control
1. Two functions of admission control
   - Determine **if a new reservation** can be setup based on the admission control policy
   - **Monitor and measure the available resources**
2. Two basic approaches to admission control
   - **Parameters based**
     - A set of parameters is used to precisely haracterize traffic flows
     - **Difficult to give accurate**, tight traffic models
   - **Measurement based**
     - The network measures the **actual traffic load** and uses that for admission control
3. Most common used methods
   - **Simple sum**: the sum of requested bandwidth for all current flows and the new flow **does not exceed the link capacity**. This is the most conservative approach
   - **Measured sum**: the measured sum approach uses the measured **load of existing flows rather than the bandwidth requested by them**
   - **Acceptance region**: **maximize the reward of utilization increases against packet losses.** Given the statistical models of traffic sources, the acceptance region for a type of traffic can be
    ![](./src/../../src/Admission%20Control%20-%20Acceptance%20region.png)
   - **Equivalent bandwidth**: the equivalent bandwidth for a set of flows is defined as the bandwidth C(p) such that the stationary bandwidth requirement of the set of flows exceeds this value with a probability of at most p (**Based on probabilistic models.**)
4. How to measure the traffic load of existing flows?
   - Exponential **averaging over consecutive measurement**:
   ```math
   NewEstimation = (1-w) * OldEstimation + w * NewMeasurement
   ```
   - Time window: the average arrival rate is measured over a sampling interval. At the end of a measurement period the **highest average is used as the estimated rate**. Suppose there are n sample intervals in a measurement period T and Ci is the average rate measured over sampling interval i; then
   ```math
   EstimationRate = max[C_1,C_2,...C_n]
   ```

# Flow Identification
1. In packet processing a router must examine every incoming packet and decide **if the packet belongs to one of the received RSVP flows**
2. The task is performed at packet classifier (inside a **router** actually)
3. Each packet is identified by five fields (five-tuple) in the packet header
<font color=red>
   - Source IP address
   - Destination IP address
   - Protocol ID
   - Source port
   - Destination port

</font>

# Packet Scheduling
1. Packet scheduling is responsible for enforcing resource 
allocation
2. Common scheduling methods
   - Fair queueing: WFQ
   - Deadline-based: EDF
   - Rate-based: virtual clock (timestamp)

---

# Service Models Defined in IntServ
## Guarantee service
1. **Provided guarantee bandwidth and strict** bounds on **end-to-end queueing delay (max)** for conforming flows
2. The end-to-end behavior of a path that supports guaranteed service can be viewed as a virtual circuit (more flexible than real circuit) with guaranteed bandwidth
3. **TSpec** (traffic specification)
   - Bucket rate r (bytes/second): the rate at which tokens arrive at the token bucket
   - Peak rate p (bytes/second): the max rate at which packets can transmit
   - Bucket depth b (bytes): the size of the token bucket
   - Min policed unit m (bytes): any packet with a size smaller than m will be counted as m bytes
   - Max packet size M (bytes): the max packet size that can be 
accepted
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
4. A service model between the best effort and guaranteed service through appropriate admission control and traffic isolation mechanisms (better-than-best-effort service)
5. End-to-end behavior
   - Very high probability that transmitted packets are successfully delivered to the destination
   -  End-to-end transit delay measured for a very high percentage of packets not greatly exceeding the min end-to-end transit delay
6. The acceptance of a request for the controlled load service implies that the network has sufficient resources to accommodate the traffic without causing congestion
7. TSpec is allowed to specify this desired traffic parameters
8. New request can be accepted only when all nodes over the path have sufficient resources available to accommodate the new flow
9. Admission control is left as a local matter
10. Traffic policing
    - When non-conformant packets arrive, the network must continue to provide the contracted service guarantees to conforming flows
    - The network should prevent the excessive controlled load traffic from unfairly impacting the best-effort traffic
    - The network must attempt to deliver the excessive traffic when it can do so without violating the previous two requirement