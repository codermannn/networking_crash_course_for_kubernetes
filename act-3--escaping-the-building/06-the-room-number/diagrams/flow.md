# Diagram: Subnet Mask & Routing Decision (Module 06)

This diagram shows how the OS kernel uses the subnet mask (the "scissors") to decide if a packet is destined for the local network or needs to go to a gateway.

```mermaid
flowchart TD
    IP["Destination IP: 10.0.2.5\n(in binary)"]
    Mask["Subnet Mask: 255.255.255.0\n(in binary: 24 ones, 8 zeros)"]
    
    AND{"Kernel performs bitwise AND:\nIP & Mask"}
    
    LocalSubnet["Local Subnet Prefix:\n10.0.1.0/24"]
    Result["Result: 10.0.2.0"]
    
    Match{"Does 10.0.2.0 match local\nsubnet 10.0.1.0?"}
    
    Shout["Local Destination!\nSend ARP shout for 10.0.2.5"]
    Map["Remote Destination!\nConsult Routing Table for gateway"]

    IP --> AND
    Mask --> AND
    AND --> Result
    Result --> Match
    LocalSubnet --> Match
    
    Match -->|Yes| Shout
    Match -->|No| Map
    
    style IP fill:#f9f9f9,stroke:#333
    style Mask fill:#f9f9f9,stroke:#333
    style Match fill:#ffe6cc,stroke:#d97706,stroke-width:1px
    style Shout fill:#d1fae5,stroke:#10b981
    style Map fill:#fee2e2,stroke:#ef4444
```
