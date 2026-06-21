# Diagram: Isolated Namespaces & Veth pairs (Module 05)

This diagram shows how the OS kernel uses network namespaces to isolate network stacks, and a virtual ethernet (`veth`) pair to create a private tunnel between them.

```mermaid
flowchart LR
    subgraph HostNamespace [Host / Root Namespace]
        subgraph NS_A [Namespace: room_a]
            veth_a["veth_a\n(Endpoint A)"]
        end

        subgraph NS_B [Namespace: room_b]
            veth_b["veth_b\n(Endpoint B)"]
        end

        veth_a <-->|"Virtual Ethernet Cable\n(veth pair)"| veth_b
    end

    style HostNamespace fill:#f9f9f9,stroke:#333,stroke-width:1px
    style NS_A fill:#ffe6cc,stroke:#d97706,stroke-width:1px
    style NS_B fill:#e6f2ff,stroke:#0066cc,stroke-width:1px
    style veth_a fill:#ffffff,stroke:#333,stroke-dasharray: 5 5
    style veth_b fill:#ffffff,stroke:#333,stroke-dasharray: 5 5
```
