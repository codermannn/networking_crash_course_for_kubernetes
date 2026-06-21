# Student Progress — Living Document

> **🔧 INSTRUCTIONS FOR THE LLM TUTOR — READ BEFORE EVERY SESSION**
>
> This file is **the single most important file for session continuity**. Any LLM tutoring this student must:
>
> 1. **READ this file at the start of every session** to know where the student left off.
> 2. **UPDATE this file at the end of every session** (or after any significant milestone mid-session).
> 3. **Never delete old entries** — append to tables, update statuses in place, add notes.
> 4. **Be specific** — "worked on Module 3" is useless. "Completed TCP handshake exercise, student can explain SYN/SYN-ACK/ACK but was confused about why TIME_WAIT exists" is gold.
> 5. **Preserve the student's voice** in the Student Notes section — quote them when possible.

---

## 1. Session Log

| # | Date | Module(s) | Duration | Key Topics Covered | Notes / Observations |
|---|------|-----------|----------|---------------------|----------------------|
| 1 | — | — | — | — | _No sessions yet_ |

---

## 2. Current State

- **Active Module:** _None_
- **Current Exercise:** _None_
- **Last Topic Discussed:** _None_
- **Student Energy / Engagement:** _None_
- **Blockers / Confusion Points:** _None_
- **Environment Status:** _Docker Desktop verified_

---

## 3. Module Completion Status

- [ ] **Module 01: The Tray** — Named pipes and local file descriptors (~15m)
- [ ] **Module 02: The Fake Tray** — TCP socket sockets as file descriptors (~20m)
- [ ] **Module 03: The Serial Number** — MAC addresses and packet filtering (~20m)
- [ ] **Module 04: The Shout** — ARP discovery and neighbor cache (~20m)
- [ ] **Module 05: The Walls** — Network namespaces and veth pairs (~25m)
- [ ] **Module 06: The Room Number** — IP addressing and subnet masks (~20m)
- [ ] **Module 07: The Map** — Routing tables and multi-hop forwarding (~25m)
- [ ] **Module 08: The Gossip** — BGP and dynamic internet routing (~20m)
- [ ] **Module 09: The Desk Number** — Port multiplexing and ss socket queries (~20m)
- [ ] **Module 10: The Registered Mail** — TCP sequence numbers and retransmissions (~25m)
- [ ] **Module 11: The Paper Airplane** — UDP connectionless transmission (~20m)
- [ ] **Module 12: The Phonebook** — DNS name resolution and resolv.conf (~20m)
- [ ] **Module 13: The Con Artist** — NAT masquerading and conntrack table (~25m)

---

## 4. Confidence Map

| Concept Area | Student Rating (1-5) | Tutor Rating (1-5) | Last Updated | Notes |
|--------------|----------------------|--------------------|--------------|-------|
| IPC / Pipes | 1 | 1 | — | — |
| File Descriptors | 1 | 1 | — | — |
| MAC / Link Layer | 1 | 1 | — | — |
| ARP Discovery | 1 | 1 | — | — |
| Namespaces | 1 | 1 | — | — |
| Subnets / CIDR | 1 | 1 | — | — |
| Routing Tables | 1 | 1 | — | — |
| BGP / Core Routes | 1 | 1 | — | — |
| TCP Mechanics | 1 | 1 | — | — |
| UDP Mechanics | 1 | 1 | — | — |
| DNS Resolution | 1 | 1 | — | — |
| NAT / Masquerade | 1 | 1 | — | — |
| Kubernetes CNI | 1 | 1 | — | — |
| K8s Services / Proxy| 1 | 1 | — | — |

---

## 5. Student Notes

*   **Confusion Point:** The student expressed confusion regarding the sequence of study: when to inspect the source code in `code/`, when to run commands inside the `lab/` workbench, and when to look at the Mermaid flow diagrams.
*   **Resolution:** Modified all 13 module READMEs to add:
    1.  A **"🗺️ The Seeker's Path: How to Study This Module"** callout at the top of every README showing the precise order of learning steps.
    2.  An **"🔍 Inspect the Code"** callout box inline before C/Python file compilation/runs, linking directly to the source code file.
    3.  A **"🗺️ Visualise the Flow"** section inline containing the embedded Mermaid diagram from `diagrams/flow.md`, explaining how the diagram maps the actions they just ran.
*   **Verification Request:** The student requested explicit instructions to verify the systems-level first-principles behavior (such as testing named pipe RAM allocation sizes, socket descriptors, and kernel namespaces) inside the `netshoot` containers.
*   **Resolution:** Injected a **"🔍 First-Principles Verification"** callout box directly inside the investigation steps of all 13 modules, giving the exact commands (e.g. reading `/proc`, `/sys`, running python limits checks) to verify kernel states.

---

## 6. Next Session Plan

*   Begin Act I, Module 01: The Tray. Walk the student through the prediction step, inspecting `tray.c`, testing the 64 KB RAM buffer capacity, and studying the Named Pipe Flow diagram.
