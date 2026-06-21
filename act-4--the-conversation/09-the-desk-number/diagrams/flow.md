# Diagram: Port Multiplexing (Module 09)

This diagram shows how the OS kernel acts as a dispatcher. It receives all packets at the network card, reads the destination port, and delivers them to the correct process's file descriptor.

```mermaid
flowchart TD
    NIC["Network Card / IP Layer\n(Destination: 172.20.0.2)"]
    
    Dispatcher{"Kernel Reads TCP Header:\nDestination Port?"}
    
    Socket80["Socket on Port 80\n(File Descriptor 3)"]
    Socket443["Socket on Port 443\n(File Descriptor 4)"]
    
    ProcA["Process A (Nginx HTTP)\nPID: 101"]
    ProcB["Process B (Nginx HTTPS)\nPID: 102"]

    NIC --> Dispatcher
    Dispatcher -->|80| Socket80
    Dispatcher -->|443| Socket443
    
    Socket80 -->|read() returns bytes| ProcA
    Socket443 -->|read() returns bytes| ProcB
    
    style NIC fill:#f9f9f9,stroke:#333
    style Dispatcher fill:#ffe6cc,stroke:#d97706,stroke-width:1px
    style Socket80 fill:#e6f2ff,stroke:#0066cc
    style Socket443 fill:#e6f2ff,stroke:#0066cc
```
