# Master Toolbox

> An alphabetical reference of every tool used in this course.
> Each entry links to the module where the tool was first introduced.

---

## cat /proc/net/nf_conntrack
**What it answers:** "What NAT translations is the kernel actively tracking?"
**First introduced:** [Module 13 · The Con Artist](act-5--making-it-human/13-the-con-artist/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `cat /proc/net/nf_conntrack` | Show all active connection tracking entries (the NAT notepad) |
| `conntrack -F` | Flush the connection tracking table |

## cat /proc/net/route
**What it answers:** "What does the kernel's raw routing map look like?"
**First introduced:** [Module 07 · The Map](act-3--escaping-the-building/07-the-map/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `cat /proc/net/route` | Show the raw hex routing table from kernel memory |

## cat /proc/net/tcp
**What it answers:** "What TCP sockets are open and which processes own them?"
**First introduced:** [Module 09 · The Desk Number](act-4--the-conversation/09-the-desk-number/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `cat /proc/net/tcp` | Show raw hex socket table (local addr, remote addr, state, inode) |

## drill / dig
**What it answers:** "What does the DNS phonebook say about this name?"
**First introduced:** [Module 12 · The Phonebook](act-5--making-it-human/12-the-phonebook/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `drill google.com` | Query DNS and show Question/Answer sections |
| `drill @8.8.8.8 google.com` | Query a specific DNS server |
| `dig +trace google.com` | Show the full recursive resolution chain |

## ethtool
**What it answers:** "What is the physical state of this network interface?"
**First introduced:** [Module 03 · The Serial Number](act-2--the-crowded-hallway/03-the-serial-number/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ethtool eth0` | Show NIC speed, duplex, link state |
| `ethtool -i eth0` | Show driver information |
| `ethtool -S eth0` | Show NIC statistics (TX/RX packets, errors) |

## ip addr
**What it answers:** "What IP addresses are assigned to my interfaces?"
**First introduced:** [Module 06 · The Room Number](act-3--escaping-the-building/06-the-room-number/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip addr show eth0` | Show IP and MAC for a specific interface |
| `ip addr add 10.0.1.1/24 dev eth0` | Assign an IP address |

## ip link
**What it answers:** "What network interfaces exist and what is their state?"
**First introduced:** [Module 03 · The Serial Number](act-2--the-crowded-hallway/03-the-serial-number/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip link show` | List all interfaces with MAC addresses |
| `ip link add type veth` | Create a virtual ethernet cable |
| `ip link set dev eth0 up` | Bring an interface up |

## ip neigh
**What it answers:** "Which hardware serial numbers (MACs) has the kernel discovered?"
**First introduced:** [Module 04 · The Shout](act-2--the-crowded-hallway/04-the-shout/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip neigh` | Show the ARP/neighbor cache |
| `ip neigh flush all` | Clear the cache (forces re-discovery) |

## ip netns
**What it answers:** "How do I create isolated network rooms (namespaces)?"
**First introduced:** [Module 05 · The Walls](act-3--escaping-the-building/05-the-walls/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip netns add <name>` | Create a new network namespace |
| `ip netns exec <name> <cmd>` | Run a command inside a namespace |
| `ip netns list` | List all namespaces |

## ip route
**What it answers:** "What routing rules does the kernel have?"
**First introduced:** [Module 07 · The Map](act-3--escaping-the-building/07-the-map/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ip route` | Show the routing table |
| `ip route add 10.0.2.0/24 via 10.0.1.254` | Add a static route |
| `ip route del 10.0.2.0/24` | Delete a route |

## ipcalc
**What it answers:** "What is the network/host split for this IP address?"
**First introduced:** [Module 06 · The Room Number](act-3--escaping-the-building/06-the-room-number/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ipcalc 10.0.1.50/24` | Show network, broadcast, host range, and binary mask |

## iptables
**What it answers:** "How do I write firewall and NAT rules?"
**First introduced:** [Module 13 · The Con Artist](act-5--making-it-human/13-the-con-artist/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `iptables -t nat -L -v` | List NAT rules |
| `iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE` | Enable NAT masquerading |

## ls -l /proc/\<PID\>/fd
**What it answers:** "What files and sockets does this process have open?"
**First introduced:** [Module 02 · The Fake Tray](act-1--two-programs-talking/02-the-fake-tray/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ls -l /proc/<PID>/fd` | List all file descriptors for a process |

## mkfifo
**What it answers:** "How do I create a shared memory tray between two programs?"
**First introduced:** [Module 01 · The Tray](act-1--two-programs-talking/01-the-tray/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `mkfifo <name>` | Create a named pipe (FIFO) |
| `ls -l <name>` | Verify it (look for the `p` flag) |

## nc (netcat)
**What it answers:** "How do I manually open a network connection and send/receive data?"
**First introduced:** [Module 02 · The Fake Tray](act-1--two-programs-talking/02-the-fake-tray/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `nc -l -p <port>` | Listen for TCP connections on a port |
| `nc <host> <port>` | Connect to a TCP listener |
| `nc -u <host> <port>` | Send UDP data |
| `nc -u -l -p <port>` | Listen for UDP data |

## ss
**What it answers:** "What sockets are currently open on this machine?"
**First introduced:** [Module 09 · The Desk Number](act-4--the-conversation/09-the-desk-number/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ss -tlnp` | Show TCP listening sockets with process names |
| `ss -ulnp` | Show UDP listening sockets with process names |
| `ss -tnp` | Show established TCP connections |

## strace
**What it answers:** "What system calls is this program making right now?"
**First introduced:** [Module 01 · The Tray](act-1--two-programs-talking/01-the-tray/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `strace -e openat,read <cmd>` | Trace only file open and read calls |
| `strace -e write <cmd>` | Trace only write calls |
| `strace -e socket,bind,listen <cmd>` | Trace socket creation calls |
| `strace -e sendto,recvfrom <cmd>` | Trace network send/receive calls |
| `strace -p <PID>` | Attach to a running process |

## /sys/class/net/
**What it answers:** "What does the kernel know about my physical hardware?"
**First introduced:** [Module 03 · The Serial Number](act-2--the-crowded-hallway/03-the-serial-number/)
**Quick reference:**
| Path | What it shows |
|------|-------------|
| `/sys/class/net/eth0/address` | The MAC address |
| `/sys/class/net/eth0/carrier` | Is the cable plugged in? (1=yes) |
| `/sys/class/net/eth0/speed` | Link speed in Mbps |
| `/sys/class/net/eth0/mtu` | Maximum Transmission Unit |

## tc (traffic control)
**What it answers:** "How do I simulate network conditions like packet loss or delay?"
**First introduced:** [Module 10 · The Registered Mail](act-4--the-conversation/10-the-registered-mail/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `tc qdisc add dev eth0 root netem loss 30%` | Simulate 30% packet loss |
| `tc qdisc add dev eth0 root netem delay 100ms` | Add 100ms latency |
| `tc qdisc del dev eth0 root` | Remove all traffic shaping |

## tcpdump
**What it answers:** "What is physically on the wire right now?"
**First introduced:** [Module 03 · The Serial Number](act-2--the-crowded-hallway/03-the-serial-number/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `tcpdump -i eth0` | Capture all traffic on an interface |
| `tcpdump -e` | Show Ethernet (MAC) headers |
| `tcpdump -n` | Don't resolve hostnames |
| `tcpdump -S` | Show absolute sequence numbers |
| `tcpdump arp` | Filter for ARP packets only |
| `tcpdump udp port 53` | Filter for DNS traffic |
| `tcpdump -w capture.pcap` | Write capture to file |

## traceroute
**What it answers:** "What path does a packet take across the network?"
**First introduced:** [Module 07 · The Map](act-3--escaping-the-building/07-the-map/)
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `traceroute <host>` | Show each hop to the destination |
| `traceroute -n <host>` | Don't resolve hostnames |
