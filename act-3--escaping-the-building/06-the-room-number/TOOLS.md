# Tools: Module 06 · The Room Number

## ip addr
**What it answers:** "How do I assign or inspect logical Room Numbers (IP addresses) on my network cards?"
**How we use it in this module:** To assign IP addresses and netmasks (subnet masks) to veth interfaces.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip addr show` | List all IP addresses on all interfaces |
| `ip addr add <IP>/<netmask> dev <interface>` | Assign an IP address and subnet to an interface |
| `ip addr del <IP>/<netmask> dev <interface>` | Remove an IP address |

---

## ipcalc
**What it answers:** "What floor prefix (network) and desk suffix (host) does this IP and subnet mask represent?"
**How we use it in this module:** To calculate subnets, broadcast ranges, and host limits.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ipcalc <IP>/<netmask>` | Show IP calculations (network, host range, broadcast address) |
| `ipcalc -b <IP>/<netmask>` | Show binary representation of the subnet AND operation |
