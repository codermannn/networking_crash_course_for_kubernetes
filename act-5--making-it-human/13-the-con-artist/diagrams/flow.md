# Diagram: NAT Masquerading & conntrack (Module 13)

This diagram shows how the NAT gateway (the con artist) intercepts outgoing traffic, replaces the private sender IP with its own public IP, and uses a lookup table (`conntrack`) to map replies back.

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'actorBkg': '#F8FAFC', 'actorBorder': '#64748B', 'lineColor': '#475569', 'signalColor': '#312E81', 'signalLineColor': '#4338CA', 'labelBoxBorderColor': '#64748B', 'labelBoxBkgColor': '#F1F5F9', 'noteBorderColor': '#CA8A04', 'noteBkgColor': '#FEF08A' }}}%%
sequenceDiagram
    participant Pod as Private Pod (10.0.1.2:1234)
    participant NAT as NAT Gateway (Router, Pub IP: 99.99.99.99)
    participant Web as Web Server (8.8.8.8:80)

    Note over Pod: Sends packet to 8.8.8.8:80<br/>Src: 10.0.1.2:1234, Dst: 8.8.8.8:80

    Pod->>NAT: Packet travels to Gateway
    
    Note over NAT: Intercepts packet<br/>Allocates public port 5555<br/>Writes to notepad (conntrack):<br/>[10.0.1.2:1234] <-> [99.99.99.99:5555]<br/>Rewrites Src: 99.99.99.99:5555, Dst: 8.8.8.8:80

    NAT->>Web: Packet forwarded to Web Server
    
    Note over Web: Receives packet<br/>Sends reply back to sender:<br/>Src: 8.8.8.8:80, Dst: 99.99.99.99:5555

    Web->>NAT: Reply packet arrives at Gateway
    
    Note over NAT: Receives reply<br/>Looks up port 5555 in notepad:<br/>"Ah, this is for 10.0.1.2:1234!"<br/>Rewrites Src: 8.8.8.8:80, Dst: 10.0.1.2:1234

    NAT->>Pod: Reply delivered to Pod!
```
