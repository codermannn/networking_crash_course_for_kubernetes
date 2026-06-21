# Tools: Module 07 · The Map

## cat /proc/net/route
**What it answers:** "What does the kernel's raw routing map look like in memory?"
**How we use it in this module:** To read the hex-encoded routing table and decode it by hand.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `cat /proc/net/route` | Dump the raw hex routing table |

---

## ip route add
**What it answers:** "How do I manually add a new map instruction to the kernel's routing table?"
**How we use it in this module:** To add static routes and default gateways.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip route add <subnet> via <gateway-IP> dev <interface>` | Add a static route to a destination subnet via a gateway |
| `ip route add default via <gateway-IP>` | Add a default route (gateway of last resort) |
| `ip route del <subnet>` | Delete a route |

---

## traceroute
**What it answers:** "What path (what chain of routers) is my packet taking to reach its destination?"
**How we use it in this module:** To watch a packet hop across routers by deliberately tweaking the TTL (Time To Live).
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `traceroute <destination>` | Trace path to a destination IP or hostname |
| `traceroute -n <destination>` | Trace path without resolving DNS names (prints raw IPs) |
