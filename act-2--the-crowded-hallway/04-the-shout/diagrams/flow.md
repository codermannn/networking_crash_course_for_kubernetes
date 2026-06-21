# Diagram: ARP Discovery Flow (Module 04)

This diagram shows how the OS kernel yells a broadcast message to discover the hardware MAC address of a destination IP, then updates its internal cache notebook (`ip neigh`).

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'actorBkg': '#F8FAFC', 'actorBorder': '#64748B', 'lineColor': '#475569', 'signalColor': '#312E81', 'signalLineColor': '#4338CA', 'labelBoxBorderColor': '#64748B', 'labelBoxBkgColor': '#F1F5F9', 'noteBorderColor': '#CA8A04', 'noteBkgColor': '#FEF08A' }}}%%
sequenceDiagram
    participant A as Machine A (172.20.0.2)
    participant Bridge as Shared Wire (Bridge)
    participant B as Machine B (172.20.0.3)

    Note over A: Needs to talk to 172.20.0.3<br/>Checks 'ip neigh' cache: empty!

    A->>Bridge: Broadcast Dst: FF:FF:FF:FF:FF:FF<br/>"Who has 172.20.0.3? Tell 172.20.0.2!"
    Bridge->>B: Delivers broadcast to all slots

    Note over B: Matches 172.20.0.3 IP!<br/>Prepares unicast reply.

    B->>Bridge: Unicast Dst: 02:42:ac:14:00:02<br/>"I have it! My MAC is 02:42:ac:14:00:03"
    Bridge->>A: Delivers directly to A

    Note over A: Writes to cache notebook:<br/>172.20.0.3 -> 02:42:ac:14:00:03

    A->>Bridge: Sends payload frame directly to B
    Bridge->>B: Delivers directly to B
```
# 
