# Diagram: BGP Gossip & AS Paths (Module 08)

This diagram shows how Autonomous Systems (large networks owned by ISPs or tech giants) gossip using BGP to advertise which IP prefixes they can reach, and the shortest AS Path wins.

```mermaid
flowchart TD
    subgraph AS300 [AS 300: Google Network]
        Prefix["Prefix: 8.8.8.0/24"]
    end

    subgraph AS200 [AS 200: Transit Provider]
        R2["BGP Router 2"]
    end

    subgraph AS100 [AS 100: Your ISP]
        R1["BGP Router 1"]
    end

    subgraph AS400 [AS 400: Malicious ISP]
        R4["BGP Router 4 (Hijacker)"]
    end

    AS300 -->|"Advertises 8.8.8.0/24\nAS Path: [300]"| AS200
    AS200 -->|"Advertises 8.8.8.0/24\nAS Path: [200, 300]"| AS100
    
    AS400 -.->|"Lies: 'I own 8.8.8.0/24!'\nAS Path: [400] (shorter!)"| AS100

    Note["Router 1 sees two paths to 8.8.8.0/24:<br/>1. Via AS200: [200, 300] (2 hops)<br/>2. Via AS400: [400] (1 hop!)<br/>Shortest path wins! Traffic is hijacked."]
    AS100 --- Note

    style AS300 fill:#d1fae5,stroke:#10b981
    style AS400 fill:#fee2e2,stroke:#ef4444
    style AS100 fill:#e6f2ff,stroke:#0066cc
    style Note fill:#fff9db,stroke:#fab005,stroke-width:1px,stroke-dasharray: 5 5
```
