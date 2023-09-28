GSM Architecture
===
🔙 [MENU README](../README.md)


# 2G
1. Mobile switching center (MSC)
   - Switching functions
   - Network interfacing
   - Common channel signaling
   - Gateway functionality
   - HLR and VLR maintenance
2. Base station controller (BSC)
   - Handoff between managed BTSs
   - Signal power level management
   - Frequency management among BTSs
3. Authentication center (AUC)
   - Deal with authentication and encryption
   - Deal with frauds and spoofing
4. Equipment identity register (EIR)
   - Database containing information about the identity of mobile 
equipment

![](../src/GSM%20Architecture%202G.png)
1. **<font color=red>There is no database in Base station system.</font>**
2. When a mobile phone exits airplane mode, it will go through the BSS to the **Core Network** and perform identity authentication with the **database to determine** if it is a legitimate user, **deciding which BSS to use**.
3. 2G networks follow European standards:
4. **MSC** Mobile switching center:  
   As similar to a CISCO switch. Beyond this point, it involves **physical cables and data centers**.
5. In 2G networks, the Mobile Switching Center (MSC) primarily **handles voice calls and text messages**. It is responsible for call routing and switching, making it a critical component in the network. While **it's not typically referred to as a "router" in the same sense as a network router**, it serves a similar function in managing and directing voice and SMS traffic within the mobile network.
6. **PSTN** : Making landline calls from a mobile phone typically involves using the Public Switched Telephone Network (PSTN) to connect the call.
7. **EIR** (Equipment Identity Register) **stores the identity** information of mobile phones, including the **IMEI** (International Mobile Equipment Identity) number, among other details. **"Register" in this context refers to a record or entry.**
8. **AUC** (Authentication Center)also the **database** and it refers to a component in a mobile network that handles **authentication and encryption** functions to ensure the security of communication between a mobile device and the network. 
9. **HLR** (Home Location Register) is like the **domicile** for mobile devices; it is **closely tied to the subscription information of each user** and provides this information when needed to ensure seamless communication.
10. **VLR**（Visitor Location Register）is a temporary registration location for mobile devices, used to manage mobile devices visiting their current location. For example, it is **used for temporary SIM cards for foreign visitors in Taiwan**.

![](../src/GSM%20Architecture%202G-1.png)
1. The upper path is for voice call transmission, while the lower path is for network data transmission.
2. In 2G, only voice calls are supported. In **2.5G, data transmission and internet access** are introduced. Therefore, you can see the term _**"Packet"**_ related to the network in the diagram.


---

# 3G
![](../src/GSM%20Architecture%203G.png)
1. The upper path is for voice call transmission, while the lower path is for network data transmission.
2. _**2G and 3G share the same core network**_, so telecom operators don't need to change the core network. However, the base stations are different, so users need to change their phones.


![](../src/GSM%20Architecture%203G-1.png)

# 4G
![](../src/GSM%20Architecture%204G.png)
1. **Serving Gateway** is the same as the previously mentioned MSC.
2. **HSS** is similar to the previously mentioned HLR,like **database**.
3. **PDN GW**(Packet Data Network Gateway) is a crucial component in LTE (Long-Term Evolution) or 4G networks. It is responsible for handling and managing data communication, allowing mobile devices to connect to the internet or corporate internal networks.
4. **MME** (Mobility Management Entity) is a vital component in LTE or 4G networks responsible for device mobility management, including **registration, authentication, location tracking, and control of mobile device connections**.
   - To verify with HSS
   - Control the Serving Gateway for tunnel establishment.
5. **PCRF**（Policy and Charging Rules Function） is responsible for managing and controlling the **policy and billing rules** for data traffic.
6. **Non-3GPP** in 4G networks refers to networks and resources **outside the 3GPP standards**. When a **4G network needs to expand or use non-3GPP resources**, it may involve utilizing other non-3GPP networks to provide services, like Wi-Fi or other wireless networks, to enhance coverage and capacity. This helps improve network performance and flexibility for various scenarios and applications.
   - For trusted networks, **direct access to the core network** is allowed.
   - For untrusted networks, **access requires passing through an agent** for authentication and security purposes.

   This concept is related to **<font color=red>heterogeneous networks (HetNets)</font>** or the use of non-3GPP networks alongside 4G networks to enhance their capabilities and coverage. 
   


![](../src/GSM%20Architecture%204G-1.png)


# Base Station System

Generation | Mobile Station | Base Station System
---------  |----------      |---------
 2G        | MS             | BS
 3G        | UE             | NodeB
 4G        | UE             | eNB(eNodeB)
 4G        | UE             | gNB

# From UMTS to LTE
![](../src/From%20UMTS%20to%20LTE.png)
> UMTS stands for "Universal Mobile Telecommunications System."

> LTE (Long-Term Evolution) is a wireless communication technology used to provide high-speed data transmission and mobile communication services.

> VoLTE (Voice over Long-Term Evolution) is a technology that allows voice calls to be transmitted over a 4G LTE (Long-Term Evolution) network. When 4G was initially introduced, our voice calls were covertly transferred to the 3G network.

## Circuit Core (Circuit Switched Core) 
   - Circuit Core is a communication system based on fixed circuit-switched connections, primarily designed to support **traditional voice calls**.
   - Call charges are typically **billed per second**, meaning that during voice calls, the communication system calculates charges based on the actual call duration.
   - Circuit Core is primarily used for handling **voice calls and ensuring stable and fixed call connections**, thus providing **high communication quality**.
## Packet Core (IP convergence)
   - Packet Core is a communication system that specializes in handling **data communication and packet-based data transmission**. It is typically used to support mobile data transmission, such as internet access, application usage, and messaging.
   - The billing method for Packet Core is typically **based on data usage rather than charging by call duration**. This means that users are billed based on the amount of data they transmit.
   - It **ensures efficient data routing, transmission**, and management to ensure users can quickly access the data and services they need.
   - The Packet Core is **<font color=red>designed with memory and buffers to address priority issues</font>** and ensure data is processed in a first-come-first-served manner.