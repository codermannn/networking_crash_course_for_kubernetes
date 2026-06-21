# Tools: Module 11 · The Paper Airplane

## nc -u
**What it answers:** "Can I send or listen for raw, connectionless UDP datagrams?"
**How we use it in this module:** To start a UDP listener and send fire-and-forget datagrams.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `nc -u -l -p <port>` | Start a UDP listener on a specific local port |
| `nc -u <IP> <port>` | Connect to a remote UDP port to send messages |

---

## tcpdump udp
**What it answers:** "Show me only the UDP packets flying across the interface."
**How we use it in this module:** To capture UDP packets and verify there are no handshakes or ACKs.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `tcpdump -i eth0 udp` | Capture only UDP packets |
| `tcpdump -i eth0 -n udp port 53` | Capture UDP packets specifically on DNS port 53 |
