# Diagram: DNS Recursive Resolution (Module 12)

This diagram shows how a name query traverses the chain of phonebooks. The C Library (`libc`) queries the local recursive resolver, which queries the hierarchy if the answer isn't cached.

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'primaryBorderColor': '#64748B', 'lineColor': '#475569' }}}%%
flowchart TD
    App["Application<br/>(e.g., curl google.com)"]
    libc["C Library (libc)<br/>getaddrinfo()"]
    Resolv["/etc/resolv.conf<br/>(Pointed to DNS Resolver)"]
    Recursive["Recursive DNS Resolver<br/>(e.g., CoreDNS or 8.8.8.8)"]
    
    Root["1. Root Nameservers<br/>('.')"]
    TLD["2. TLD Nameservers<br/>('.com')"]
    Auth["3. Authoritative Nameservers<br/>('google.com')"]

    App -->|1. Lookup name| libc
    libc -->|2. Reads resolv.conf, sends UDP| Resolv
    Resolv -->|3. Queries port 53| Recursive
    
    Recursive -->|4. Where is .com?| Root
    Root -->|5. Go to TLD IP| Recursive
    Recursive -->|6. Where is google.com?| TLD
    TLD -->|7. Go to Authoritative IP| Recursive
    Recursive -->|8. What is google.com's IP?| Auth
    Auth -->|9. It is 142.250.190.46| Recursive
    
    Recursive -->|10. Returns IP| libc
    libc -->|11. Returns IP to Application| App

    style App fill:#F8FAFC,stroke:#64748B,stroke-width:1px
    style libc fill:#F8FAFC,stroke:#64748B,stroke-width:1px
    style Resolv fill:#FFF7ED,stroke:#EA580C,stroke-width:1px
    style Recursive fill:#E0E7FF,stroke:#4F46E5,stroke-width:1.5px
    style Root fill:#EEF2F6,stroke:#475569,stroke-width:1px
    style TLD fill:#EEF2F6,stroke:#475569,stroke-width:1px
    style Auth fill:#EEF2F6,stroke:#475569,stroke-width:1px
```
