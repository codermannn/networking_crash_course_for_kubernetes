# Tools: Module 03 · The Serial Number

## tcpdump -e
**What it answers:** "Show me the raw ethernet packets flying past including their MAC addresses."
**How we use it in this module:** To see the source and destination hardware addresses wrapped around the payload.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `tcpdump -i eth0 -e` | Capture packets on `eth0` and print link-level headers (MAC addresses) |
| `tcpdump -i eth0 -e icmp` | Capture only ICMP (ping) packets showing MAC headers |

---

## /sys/class/net/eth0/address
**What it answers:** "What is the hardware serial number (MAC address) burned into my interface?"
**How we use it in this module:** To read the local MAC address directly from the kernel filesystem representation.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `cat /sys/class/net/eth0/address` | Print the MAC address of `eth0` |

---

## ethtool
**What it answers:** "What are the hardware properties, drivers, and speed of this network card (NIC)?"
**How we use it in this module:** To inspect the physical properties of our network card.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ethtool eth0` | Show speed, duplex, auto-negotiation, and link detection for `eth0` |
| `ethtool -i eth0` | Show driver info (e.g. `veth` driver) |

---

## ip link
**What it answers:** "What network links exist and how do I configure them?"
**How we use it in this module:** To inspect interfaces, bring them up/down, and spoof/change MAC addresses.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip link show` | List all interfaces and their MAC addresses |
| `ip link set eth0 address <new-MAC>` | Spoof/change the MAC address of `eth0` (requires root privileges) |
