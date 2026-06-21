# Diagram: Socket Connection Flow (Module 02)

This diagram shows how the OS kernel translates standard read/write file system calls into network packets, keeping the network card (NIC) and wires hidden behind a File Descriptor "mask."

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'actorBkg': '#F8FAFC', 'actorBorder': '#64748B', 'lineColor': '#475569', 'signalColor': '#312E81', 'signalLineColor': '#4338CA', 'labelBoxBorderColor': '#64748B', 'labelBoxBkgColor': '#F1F5F9', 'noteBorderColor': '#CA8A04', 'noteBkgColor': '#FEF08A' }}}%%
sequenceDiagram
    participant Client as Client (machine_a)
    participant CKernel as Client Kernel
    participant SKernel as Server Kernel
    participant Server as Server (machine_b)

    Note over Server: server_fd = socket()
    Note over Server: bind(server_fd, port 8080)
    Note over Server: listen(server_fd)
    Server->>SKernel: accept() [blocks]

    Note over Client: sock_fd = socket()
    Client->>CKernel: connect(sock_fd, machine_b_ip:8080)
    
    CKernel->>SKernel: TCP Syn Packet (over the wire)
    SKernel->>CKernel: TCP Syn-Ack
    CKernel->>SKernel: TCP Ack
    
    SKernel-->>Server: accept() unblocks, returns new fd (3)
    CKernel-->>Client: connect() returns 0

    Client->>CKernel: write(sock_fd, "Hello!")
    CKernel->>SKernel: Ethernet frame carrying TCP packet
    SKernel->>Server: read(3) returns "Hello!"
```
