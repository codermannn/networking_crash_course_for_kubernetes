# Diagram: Port Multiplexing (Module 09)

This diagram shows how the OS kernel acts as a dispatcher. It receives all packets at the network card, reads the destination port, and delivers them to the correct process's file descriptor.

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'primaryBorderColor': '#64748B', 'lineColor': '#475569' }}}%%
flowchart TD
    NIC["Network Card / IP Layer<br/>(Destination: 172.20.0.2)"]
    
    Dispatcher{"Kernel Reads TCP Header:<br/>Destination Port?"}
    
    Socket80["Socket on Port 80<br/>(File Descriptor 3)"]
    Socket443["Socket on Port 443<br/>(File Descriptor 4)"]
    
    ProcA["Process A (Nginx HTTP)<br/>PID: 101"]
    ProcB["Process B (Nginx HTTPS)<br/>PID: 102"]

    NIC --> Dispatcher
    Dispatcher -->|80| Socket80
    Dispatcher -->|443| Socket443
    
    Socket80 -->|read() returns bytes| ProcA
    Socket443 -->|read() returns bytes| ProcB
    
    style NIC fill:#F8FAFC,stroke:#64748B,stroke-width:1px
    style Dispatcher fill:#FFF7ED,stroke:#EA580C,stroke-width:1px
    style Socket80 fill:#E0E7FF,stroke:#4F46E5,stroke-width:1.5px
    style Socket443 fill:#E0E7FF,stroke:#4F46E5,stroke-width:1.5px
    style ProcA fill:#ECFDF5,stroke:#059669,stroke-width:1px
    style ProcB fill:#ECFDF5,stroke:#059669,stroke-width:1px
```
