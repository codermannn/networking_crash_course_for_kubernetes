# Diagram: Isolated Namespaces & Veth pairs (Module 05)

This diagram shows how the OS kernel uses network namespaces to isolate network stacks, and a virtual ethernet (`veth`) pair to create a private tunnel between them.

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'primaryBorderColor': '#64748B', 'lineColor': '#475569' }}}%%
flowchart LR
    subgraph HostNamespace ["Host / Root Namespace"]
        subgraph NS_A ["Namespace: room_a"]
            veth_a["veth_a<br/>(Endpoint A)"]
        end

        subgraph NS_B ["Namespace: room_b"]
            veth_b["veth_b<br/>(Endpoint B)"]
        end

        veth_a <-->|"Virtual Ethernet Cable<br/>(veth pair)"| veth_b
    end

    style HostNamespace fill:#F8FAFC,stroke:#64748B,stroke-width:1.5px
    style NS_A fill:#FFF7ED,stroke:#EA580C,stroke-width:1.5px
    style NS_B fill:#E0E7FF,stroke:#4F46E5,stroke-width:1.5px
    style veth_a fill:#ffffff,stroke:#475569,stroke-width:1px,stroke-dasharray: 5 5
    style veth_b fill:#ffffff,stroke:#475569,stroke-width:1px,stroke-dasharray: 5 5
```
