# Diagram: Named Pipe Flow (Module 01)

This diagram shows how the OS kernel manages memory (the "tray") to pass bytes between two isolated processes on the same machine without touching the disk.

```mermaid
%%{init: { 'theme': 'neutral', 'themeVariables': { 'primaryColor': '#F8FAFC', 'primaryBorderColor': '#64748B', 'lineColor': '#475569' }}}%%
flowchart TD
    subgraph Userspace ["Userspace: Isolated Memory"]
        A["Terminal A (Writer)<br/>PID: 101"] 
        B["Terminal B (Reader)<br/>PID: 102"]
    end

    subgraph Kernel ["Kernelspace: Shared Memory"]
        FIFO["Named Pipe Buffer<br/>('/tmp/my_tray' in RAM)"]
        Matchmaker{"Both Reader & Writer<br/>present?"}
    end

    A -->|"1. open(FIFO, O_WRONLY)"| Matchmaker
    B -->|"2. open(FIFO, O_RDONLY)"| Matchmaker

    Matchmaker -->|Yes| Unblock["Unblock both processes"]
    Unblock -->|"3. write(fd, msg)"| FIFO
    FIFO -->|"4. read(fd, buf)"| B

    style Userspace fill:#F8FAFC,stroke:#64748B,stroke-width:1.5px
    style Kernel fill:#EEF2F6,stroke:#475569,stroke-width:1.5px
    style FIFO fill:#FEF3C7,stroke:#D97706,stroke-width:1.5px
    style Unblock fill:#ECFDF5,stroke:#059669,stroke-width:1.5px
```
