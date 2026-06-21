# Tools: Module 13 · The Con Artist

## iptables -t nat
**What it answers:** "How do I configure the kernel to rewrite IP addresses or port numbers on packets?"
**How we use it in this module:** To set up masquerading (NAT) to translate private subnets into public IPs.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `iptables -t nat -S` | List all configured NAT rules |
| `iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE` | Turn on NAT masquerading for traffic leaving `eth0` |
| `iptables -t nat -F` | Flush all NAT rules |

---

## cat /proc/net/nf_conntrack
**What it answers:** "Which NAT mappings (original IP/port vs. rewritten IP/port) is the kernel currently tracking?"
**How we use it in this module:** To inspect the conntrack state table.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `cat /proc/net/nf_conntrack` | Dump all active connection tracking entries |
| `conntrack -F` | Clear/flush all active tracked connections (deletes the con artist's notes) |
