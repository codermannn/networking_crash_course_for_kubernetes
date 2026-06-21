# Tools: Module 05 · The Walls

## ip netns
**What it answers:** "How do I create and manage isolated network rooms (namespaces) inside Linux?"
**How we use it in this module:** To create isolated environments (rooms) and execute commands inside them.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip netns add <name>` | Create a new network namespace (room) |
| `ip netns exec <name> <command>` | Run a command inside a namespace |
| `ip netns list` | List all network namespaces |
| `ip netns del <name>` | Delete a namespace |

---

## ip link (veth configuration)
**What it answers:** "How do I create virtual cables (veth pairs) to connect my isolated rooms?"
**How we use it in this module:** To build a virtual cable and thread its ends into separate network namespaces.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip link add <name1> type veth peer name <name2>` | Create a veth pair (virtual ethernet cable with two ends) |
| `ip link set <interface> netns <namespace>` | Move one end of the cable into a namespace |
| `ip netns exec <ns> ip link set dev <interface> up` | Bring the interface up inside the namespace |
