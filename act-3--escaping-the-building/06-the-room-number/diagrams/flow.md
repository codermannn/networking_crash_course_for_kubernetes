# Diagram: Subnet Mask & Routing Decision (Module 06)

This diagram shows how the OS kernel uses the subnet mask (the "scissors") to decide if a packet is destined for the local network or needs to go to a gateway.

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'primaryBorderColor': '#64748B', 'lineColor': '#475569' }}}%%
flowchart TD
    IP["Destination IP: 10.0.2.5<br/>(in binary)"]
    Mask["Subnet Mask: 255.255.255.0<br/>(in binary: 24 ones, 8 zeros)"]
    
    AND{"Kernel performs bitwise AND:<br/>IP & Mask"}
    
    LocalSubnet["Local Subnet Prefix:<br/>10.0.1.0/24"]
    Result["Result: 10.0.2.0"]
    
    Match{"Does 10.0.2.0 match local<br/>subnet 10.0.1.0?"}
    
    Shout["Local Destination!<br/>Send ARP shout for 10.0.2.5"]
    Map["Remote Destination!<br/>Consult Routing Table for gateway"]

    IP --> AND
    Mask --> AND
    AND --> Result
    Result --> Match
    LocalSubnet --> Match
    
    Match -->|Yes| Shout
    Match -->|No| Map
    
    style IP fill:#F8FAFC,stroke:#64748B,stroke-width:1px
    style Mask fill:#F8FAFC,stroke:#64748B,stroke-width:1px
    style AND fill:#EEF2F6,stroke:#475569,stroke-width:1px
    style Match fill:#FFF7ED,stroke:#EA580C,stroke-width:1px
    style Shout fill:#ECFDF5,stroke:#059669,stroke-width:1.5px
    style Map fill:#FFF1F2,stroke:#E11D48,stroke-width:1.5px
```
