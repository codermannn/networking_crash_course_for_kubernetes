# Tools: Module 08 · The Gossip

## traceroute (with AS lookup)
**What it answers:** "Which Autonomous Systems (AS) is my packet traversing to cross the internet?"
**How we use it in this module:** To trace paths across autonomous systems and identify ISP boundaries.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `traceroute -n <domain>` | Trace IP hops without resolving names |
| `traceroute -A <domain>` | Trace path and display the AS (Autonomous System) number for each hop |

---

## whois (AS querying)
**What it answers:** "Who owns this IP address block and what AS number is advertising it?"
**How we use it in this module:** To look up ownership and BGP advertisements of routers.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `whois <IP>` | Look up IP block registration data |
| `whois -h whois.radb.net <IP>` | Query route database for BGP prefix allocations |
