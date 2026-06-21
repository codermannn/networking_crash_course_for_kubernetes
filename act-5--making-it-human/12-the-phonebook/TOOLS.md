# Tools: Module 12 · The Phonebook

## drill / dig
**What it answers:** "What IP addresses are mapped to this human-friendly domain name?"
**How we use it in this module:** To query DNS servers and trace the resolution path.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `drill google.com` | Query the default DNS resolver for `google.com` |
| `drill @8.8.8.8 google.com` | Query a specific DNS resolver (Google's Public DNS) |
| `dig +trace google.com` | Query DNS and display the recursive root-to-authoritative lookup path |

---

## cat /etc/resolv.conf
**What it answers:** "Which DNS phonebooks is my computer configured to query?"
**How we use it in this module:** To inspect the nameserver IP addresses configured inside the container.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `cat /etc/resolv.conf` | View configured DNS nameservers |
