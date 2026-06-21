# Diagram: TCP vs. UDP Protocol Overhead (Module 11)

This diagram shows the comparison between the heavy, safe TCP protocol and the lightweight, fast UDP protocol.

```mermaid
flowchart TD
    subgraph TCP ["TCP (Registered Mail)"]
        direction TB
        T1["1. Handshake\n(SYN -> SYN-ACK -> ACK)"]
        T2["2. Send Segment 1"]
        T3["3. Wait for ACK 1"]
        T4["4. Send Segment 2"]
        T5["5. Wait for ACK 2"]
        T6["6. Connection Teardown\n(FIN -> ACK -> FIN -> ACK)"]
        
        T1 --> T2 --> T3 --> T4 --> T5 --> T6
    end

    subgraph UDP ["UDP (Paper Airplane)"]
        direction TB
        U1["1. Send Datagram 1"]
        U2["2. Send Datagram 2"]
        U3["3. Send Datagram 3"]
        
        U1 --> U2 --> U3
    end

    style TCP fill:#e6f2ff,stroke:#0066cc
    style UDP fill:#ffe6cc,stroke:#d97706
```
