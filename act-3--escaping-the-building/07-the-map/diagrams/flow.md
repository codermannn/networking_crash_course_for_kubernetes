# Diagram: Multi-hop Routing & MAC Rewrites (Module 07)

This diagram shows how a packet travels across floors (subnets). The logical IP addresses stay the same, but the hardware MAC addresses are rewritten at each hop.

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'actorBkg': '#F8FAFC', 'actorBorder': '#64748B', 'lineColor': '#475569', 'signalColor': '#312E81', 'signalLineColor': '#4338CA', 'labelBoxBorderColor': '#64748B', 'labelBoxBkgColor': '#F1F5F9', 'noteBorderColor': '#CA8A04', 'noteBkgColor': '#FEF08A' }}}%%
sequenceDiagram
    participant A as Room A (10.0.1.1, MAC: AA)
    participant Router as Router (10.0.1.254 / 10.0.2.254, MAC: RR)
    participant B as Room B (10.0.2.1, MAC: BB)

    Note over A: Needs to send to 10.0.2.1<br/>Dst is remote, sends to Gateway (10.0.1.254)<br/>Dst MAC: RR, Dst IP: 10.0.2.1

    A->>Router: Frame flies to Router
    
    Note over Router: Receives frame<br/>Consults routing table for 10.0.2.1<br/>Matches subnet 10.0.2.0/24<br/>Rewrites Dst MAC: BB, Dst IP: 10.0.2.1

    Router->>B: Frame flies to B
    Note over B: Receives frame successfully!
```
