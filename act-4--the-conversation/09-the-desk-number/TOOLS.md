# Tools: Module 09 · The Desk Number

## ss
**What it answers:** "Which sockets are active, which ports are they bound to, and what processes own them?"
**How we use it in this module:** To inspect the port mappings on our host and container.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ss -tln` | List all listening TCP sockets (ports) |
| `ss -tlnp` | List listening TCP sockets showing the process name and PID owning each |
| `ss -ta` | List all TCP sockets (both listening and active connections) |

---

## cat /proc/net/tcp
**What it answers:** "What TCP sockets does the kernel have active in raw hex format?"
**How we use it in this module:** To read the kernel's raw socket table directly from memory and decode the port hex.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `cat /proc/net/tcp` | Dump the TCP socket table |
