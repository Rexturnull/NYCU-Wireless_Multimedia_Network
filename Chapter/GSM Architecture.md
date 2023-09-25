GSM Architecture
===
🔙 [MENU README](../README.md)


# 2G
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

# 3G
![](../src/GSM%20Architecture%203G.png)
![](../src/GSM%20Architecture%203G-1.png)

# 4G
![](../src/GSM%20Architecture%204G.png)
![](../src/GSM%20Architecture%204G-1.png)
# 5G


# Base Station System
Generation | Mobile Station | Base Station System
---------  |----------      |---------
 2G        | MS             | BS
 3G        | UE             | NodeB
 4G        | UE             | eNB(eNodeB)
 4G        | UE             | gNB


