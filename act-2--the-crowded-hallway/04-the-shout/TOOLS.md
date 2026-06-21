# Tools: Module 04 · The Shout

## ip neigh
**What it answers:** "What hardware serial numbers (MACs) has the kernel discovered and cached for local IP addresses?"
**How we use it in this module:** To inspect, flush, and manually configure the kernel's neighbor lookup table.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip neigh` | Show all cached ARP table entries |
| `ip neigh flush all` | Delete all cached entries (forces re-discovery) |
| `ip neigh replace <IP> lladdr <MAC> dev <interface>` | Add or update a static MAC mapping (prevents shouts) |

---

## tcpdump arp
**What it answers:** "Show me only the ARP shouting and replying packets on the network."
**How we use it in this module:** To watch the ARP broadcast frame being yelled to all machines.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `tcpdump -i eth0 arp` | Capture only ARP packets |
| `tcpdump -i eth0 arp -en` | Capture ARP packets showing hardware MACs and raw IPs |
