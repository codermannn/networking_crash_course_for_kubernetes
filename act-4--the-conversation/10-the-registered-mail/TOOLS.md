# Tools: Module 10 · The Registered Mail

## tc qdisc
**What it answers:** "How do I simulate network degradation (like packet loss, latency, or corruption) on my network interface?"
**How we use it in this module:** To introduce a 30% packet loss on `eth0` to test TCP's reliability.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `tc qdisc show dev eth0` | Show active queuing disciplines for `eth0` |
| `tc qdisc add dev eth0 root netem loss 30%` | Add 30% packet loss to `eth0` |
| `tc qdisc del dev eth0 root` | Remove all network emulation configurations |

---

## tcpdump -S
**What it answers:** "Show me the absolute TCP sequence numbers on the wire."
**How we use it in this module:** To trace TCP handshakes, sequence counts, duplicate ACKs, and retransmissions.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `tcpdump -i eth0 -S -n tcp` | Capture TCP packets displaying absolute sequence numbers |
| `tcpdump -i eth0 -S -n tcp port 8080` | Capture TCP packets specifically on port 8080 |
