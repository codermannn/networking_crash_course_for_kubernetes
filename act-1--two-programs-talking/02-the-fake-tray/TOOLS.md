# Tools: Module 02 · The Fake Tray

## nc (netcat)
**What it answers:** "Can I establish a raw TCP connection to a specific port and send/receive bytes?"
**How we use it in this module:** To manually send message strings from `machine_a` to a listening socket on `machine_b`.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `nc -l -p <port>` | Start a TCP listener on a specific local port |
| `nc <ip> <port>` | Connect to a remote TCP port |

---

## strace (focused on Socket calls)
**What it answers:** "What socket-specific system calls is this network program making?"
**How we use it in this module:** To watch `socket()`, `bind()`, `listen()`, `connect()`, and `accept()` calls.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `strace -e socket,bind,listen,accept,connect <cmd>` | Trace only networking system calls |

---

## /proc/<PID>/fd/
**What it answers:** "What files, sockets, or pipes does a running process have open?"
**How we use it in this module:** To see that a socket is assigned a simple File Descriptor integer just like a local file.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ls -l /proc/<PID>/fd/` | List file descriptor links for a running process |
