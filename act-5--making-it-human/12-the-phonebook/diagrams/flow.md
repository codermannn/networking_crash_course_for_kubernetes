# Diagram: DNS Recursive Resolution (Module 12)

This diagram shows how a name query traverses the chain of phonebooks. The C Library (`libc`) queries the local recursive resolver, which queries the hierarchy if the answer isn't cached.

```mermaid
flowchart TD
    App["Application\n(e.g., curl google.com)"]
    libc["C Library (libc)\ngetaddrinfo()"]
    Resolv["/etc/resolv.conf\n(Pointed to DNS Resolver)"]
    Recursive["Recursive DNS Resolver\n(e.g., CoreDNS or 8.8.8.8)"]
    
    Root["1. Root Nameservers\n('.')"]
    TLD["2. TLD Nameservers\n('.com')"]
    Auth["3. Authoritative Nameservers\n('google.com')"]

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

    style App fill:#f9f9f9,stroke:#333
    style libc fill:#ffffff,stroke:#333
    style Resolv fill:#ffe6cc,stroke:#d97706
    style Recursive fill:#e6f2ff,stroke:#0066cc
```
# 
