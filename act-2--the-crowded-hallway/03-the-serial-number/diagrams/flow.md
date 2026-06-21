# Diagram: Ethernet Frame Filtering (Module 03)

This diagram shows how three machines sharing a virtual wire receive all data, but only the machine matching the Destination MAC address processes it.

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'actorBkg': '#F8FAFC', 'actorBorder': '#64748B', 'lineColor': '#475569', 'signalColor': '#312E81', 'signalLineColor': '#4338CA', 'labelBoxBorderColor': '#64748B', 'labelBoxBkgColor': '#F1F5F9', 'noteBorderColor': '#CA8A04', 'noteBkgColor': '#FEF08A' }}}%%
sequenceDiagram
    participant A as Machine A (MAC: AA:AA)
    participant Bridge as Shared Wire (Bridge)
    participant B as Machine B (MAC: BB:BB)
    participant C as Machine C (MAC: CC:CC)

    Note over A: Envelope prepared:<br/>Src MAC: AA:AA<br/>Dst MAC: BB:BB<br/>Payload: "Hello B"

    A->>Bridge: Transmits Electrical Signals
    Bridge->>B: Delivers frame (promiscuous read)
    Bridge->>C: Delivers frame (promiscuous read)

    Note over B: NIC checks Dst MAC:<br/>"BB:BB matches my serial number!"<br/>Interrupts OS, copies to RAM.
    B->>B: Process payload

    Note over C: NIC checks Dst MAC:<br/>"BB:BB does not match CC:CC."<br/>Drops frame in hardware.<br/>OS is never interrupted.
```
