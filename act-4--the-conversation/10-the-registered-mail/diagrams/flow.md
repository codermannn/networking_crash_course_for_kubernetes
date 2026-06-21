# Diagram: TCP Handshake & Retransmission (Module 10)

This diagram shows how TCP handles packet loss. The sender numbers every byte, and the receiver acknowledges the highest contiguous byte received.

```mermaid
sequenceDiagram
    participant Sender as TCP Sender
    participant Wire as Unreliable Wire (30% Loss)
    participant Receiver as TCP Receiver

    Note over Sender, Receiver: 1. TCP 3-Way Handshake
    Sender->>Wire: SYN (seq=100)
    Wire->>Receiver: SYN (seq=100)
    Receiver->>Wire: SYN-ACK (seq=500, ack=101)
    Wire->>Sender: SYN-ACK (seq=500, ack=101)
    Sender->>Wire: ACK (seq=101, ack=501)
    Wire->>Receiver: ACK (seq=101, ack=501)

    Note over Sender, Receiver: 2. Data Transmission with Packet Loss
    Sender->>Wire: Data Segment 1 (seq=101, len=100)
    Wire->>Receiver: Data Segment 1 (seq=101, len=100)
    Note over Receiver: Receives bytes 101-200.<br/>Sends ACK 201.
    Receiver->>Wire: ACK (ack=201)
    Wire->>Sender: ACK (ack=201)

    Sender->>Wire: Data Segment 2 (seq=201, len=100)
    Note over Wire: Packet dropped on wire!
    
    Sender->>Wire: Data Segment 3 (seq=301, len=100)
    Wire->>Receiver: Data Segment 3 (seq=301, len=100)
    
    Note over Receiver: Gap detected!<br/>Expected 201, got 301.<br/>Sends Duplicate ACK 201.
    Receiver->>Wire: ACK (ack=201)
    Wire->>Sender: ACK (ack=201)

    Note over Sender: Retransmission timer fires<br/>or duplicate ACKs trigger retransmit.
    Sender->>Wire: Data Segment 2 (seq=201, len=100)
    Wire->>Receiver: Data Segment 2 (seq=201, len=100)
    
    Note over Receiver: Receives 201-300.<br/>Now has everything up to 400.<br/>Sends ACK 401.
    Receiver->>Wire: ACK (ack=401)
    Wire->>Sender: ACK (ack=401)
```
