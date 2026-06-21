# Diagram: Named Pipe Flow (Module 01)

This diagram shows how the OS kernel manages memory (the "tray") to pass bytes between two isolated processes on the same machine without touching the disk.

```mermaid
flowchart TD
    subgraph Userspace [Userspace (Isolated Memory)]
        A["Terminal A (Writer)\nPID: 101"] 
        B["Terminal B (Reader)\nPID: 102"]
    end

    subgraph Kernel [Kernelspace (Shared Memory)]
        FIFO["Named Pipe Buffer\n('/tmp/my_tray' in RAM)"]
        Matchmaker{"Both Reader & Writer\npresent?"}
    end

    A -->|"1. open(FIFO, O_WRONLY)"| Matchmaker
    B -->|"2. open(FIFO, O_RDONLY)"| Matchmaker

    Matchmaker -->|Yes| Unblock["Unblock both processes"]
    Unblock -->|"3. write(fd, msg)"| FIFO
    FIFO -->|"4. read(fd, buf)"| B

    style Userspace fill:#f9f9f9,stroke:#333,stroke-width:1px
    style Kernel fill:#e6f2ff,stroke:#0066cc,stroke-width:1px
    style FIFO fill:#ffe6cc,stroke:#d97706,stroke-width:1px
```
