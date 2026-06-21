# Diagram: BGP Gossip & AS Paths (Module 08)

This diagram shows how Autonomous Systems (large networks owned by ISPs or tech giants) gossip using BGP to advertise which IP prefixes they can reach, and the shortest AS Path wins.

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'primaryBorderColor': '#64748B', 'lineColor': '#475569' }}}%%
flowchart TD
    subgraph AS300 ["AS 300: Google Network"]
        Prefix["Prefix: 8.8.8.0/24"]
    end

    subgraph AS200 ["AS 200: Transit Provider"]
        R2["BGP Router 2"]
    end

    subgraph AS100 ["AS 100: Your ISP"]
        R1["BGP Router 1"]
    end

    subgraph AS400 ["AS 400: Malicious ISP"]
        R4["BGP Router 4 (Hijacker)"]
    end

    AS300 -->|"Advertises 8.8.8.0/24<br/>AS Path: [300]"| AS200
    AS200 -->|"Advertises 8.8.8.0/24<br/>AS Path: [200, 300]"| AS100
    
    AS400 -.->|"Lies: 'I own 8.8.8.0/24!'<br/>AS Path: [400] (shorter!)"| AS100

    Note["Router 1 sees two paths to 8.8.8.0/24:<br/>1. Via AS200: [200, 300] (2 hops)<br/>2. Via AS400: [400] (1 hop!)<br/>Shortest path wins! Traffic is hijacked."]
    AS100 --- Note

    style AS300 fill:#ECFDF5,stroke:#059669,stroke-width:1.5px
    style AS200 fill:#F8FAFC,stroke:#64748B,stroke-width:1.5px
    style AS100 fill:#E0E7FF,stroke:#4F46E5,stroke-width:1.5px
    style AS400 fill:#FFF1F2,stroke:#E11D48,stroke-width:1.5px
    style Note fill:#FEF08A,stroke:#CA8A04,stroke-width:1px,stroke-dasharray: 5 5
```
