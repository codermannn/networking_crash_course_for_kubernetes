# Course Manifest — Structure & Objectives

This manifest outlines the 13-module progression of the Networking Crash Course, mapping out how the student builds networking from named pipes up to Kubernetes primitives.

---

## The Module Map

- **Act I: Two Programs Talking**
  - **Module 01: The Tray** — Named pipes and local file descriptors.
  - **Module 02: The Fake Tray** — TCP socket files across virtual wires.

- **Act II: The Crowded Hallway**
  - **Module 03: The Serial Number** — MAC addresses and packet filtering.
  - **Module 04: The Shout** — ARP neighbor resolution and cache tables.

- **Act III: Escaping the Building**
  - **Module 05: The Walls** — Network namespaces and veth isolation.
  - **Module 06: The Room Number** — IP routing subnets and CIDR masks.
  - **Module 07: The Map** — Routing tables and hex proc decoding.
  - **Module 08: The Gossip** — BGP internet routing dynamic paths.

- **Act IV: The Conversation**
  - **Module 09: The Desk Number** — Ports, listening sockets, and ss mapping.
  - **Module 10: The Registered Mail** — TCP sequence numbers and loss recovery.
  - **Module 11: The Paper Airplane** — UDP connectionless transmission.

- **Act V: Making It Human**
  - **Module 12: The Phonebook** — DNS name resolution and resolv.conf.
  - **Module 13: The Con Artist** — NAT masquerading and conntrack table.

---

## Key Learning Outcomes

By the end of this course, the student will be able to:
1. Identify how all container networking constructs map to basic Linux primitives (namespaces, veth pairs, iptables, routing).
2. Trace packets using `tcpdump` and system calls using `strace`.
3. Read and translate raw kernel network configuration tables under `/proc/net/`.
4. Explain how Kubernetes CNI plugins, Service proxies (kube-proxy), and CoreDNS work at the systems level.
