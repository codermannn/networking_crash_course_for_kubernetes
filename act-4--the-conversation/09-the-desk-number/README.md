# Act IV: The Conversation · Five people in the room. Who opens the mail?

> **You are here:** Act IV · Question 9 of 13
> **Time:** ~20 minutes
> **Tools you'll meet:** `ss -tlnp`, `cat /proc/net/tcp`
> **Prerequisites:** [Module 08: The Gossip](../../act-3--escaping-the-building/08-the-gossip/)

---

## The Situation

We can now route packets across the globe to reach our destination machine. 

But when the packet arrives at the door of the computer (`172.20.0.2`), it has only reached the threshold. Inside the room (the container), there are multiple people (processes) sitting at separate desks.
- A Web Server (Nginx) is running.
- A Database (Postgres) is running.
- A monitoring agent (Prometheus) is running.

They all share the exact same network card and IP address. 

When a packet containing a database query arrives, how does the kernel decide which process gets the bytes? Why doesn't the database query go to the Web Server?

We need **Desk Numbers** (Ports).

---

## Your Prediction

> [!IMPORTANT]
> **Before running any commands, pause and reflect:**
> Can one single program bind to two different port numbers at the same time? Or is a program restricted to only one desk number?

---

## The Lab

Start the port workbench:

```bash
cd act-4--the-conversation/09-the-desk-number/lab
docker compose down
docker compose up -d
docker compose exec workbench bash
```

Open a second terminal window and exec into the same container:
```bash
docker exec -it port_workbench bash
```

---

## The Investigation

Let's inspect the desks. We will compile a custom C program `multi_listen.c` that starts a single program that binds to two desks (Port 80 and Port 443) using the `select()` system call.

### Step 1: Compile and Run the Multi-Listener

In Terminal 1, compile and run the program:

**Run this:**
```bash
gcc -o /lab/code/multi_listen /lab/code/multi_listen.c
/lab/code/multi_listen
```

**What to look for:**
It prints:
```text
Listening on port 80 (descriptor 3) and port 443 (descriptor 4)...
```
It is now blocking, waiting for connections.

---

### Step 2: Connect to Both Desks

In Terminal 2, send messages to both Port 80 and Port 443 using `nc`:

**Run this:**
```bash
nc localhost 80
nc localhost 443
```

**What to look for:**
For port 80, it prints `HTTP Hello!`. For port 443, it prints `HTTPS Hello!`. 
In Terminal 1, the C program prints:
```text
Connection received on Port 80 (HTTP desk)!
Connection received on Port 443 (HTTPS desk)!
```

**What it means:**
A single process can open multiple socket descriptors (`3` and `4`) and bind them to different ports. The kernel reads the TCP header's destination port field and wakes up the correct file descriptor.

---

### Step 3: Inspect the Desks using `ss`

In Terminal 2, look at the active listeners:

**Run this:**
```bash
ss -tlnp
```

**What to look for:**
You will see two lines owned by the `multi_listen` process:
```text
State    Recv-Q   Send-Q      Local Address:Port      Peer Address:Port   Process
LISTEN   0        3                 0.0.0.0:80             0.0.0.0:*      users:(("multi_listen",pid=123,fd=3))
LISTEN   0        3                 0.0.0.0:443            0.0.0.0:*      users:(("multi_listen",pid=123,fd=4))
```

**What it means:**
`ss` queries the kernel to show which process ID (PID) owns which port. Port 80 is owned by descriptor `3` and Port 443 is owned by descriptor `4` of PID `123`.

---

### Step 4: Read the Kernel's Raw Desk Table

Let's read the raw hex table in kernel memory.

**Run this:**
```bash
cat /proc/net/tcp
```

**What to look for:**
A table showing local addresses in hex:
```text
  sl  local_address rem_address   st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode
   0: 00000000:0050 00000000:0000 0A 00000000:00000000 00:00000000 00000000     0        0 12345 1
   1: 00000000:01BB 00000000:0000 0A 00000000:00000000 00:00000000 00000000     0        0 12346 1
```

**What it means:**
Let's decode the local address column:
- `00000000` is the IP `0.0.0.0` (INADDR_ANY).
- `0050` is the port in hex. Convert `50` hex to decimal: `5 * 16 = 80`. This is Port 80!
- `01BB` is port in hex. Convert `1BB` hex: `1 * 256 + 11 * 16 + 11 = 256 + 176 + 11 = 443`. This is Port 443!
- `st` column shows state `0A` which is hex for `10`. State `10` is `TCP_LISTEN`.

This table is the kernel's master dispatch sheet.

---

## The Evidence

Every socket in Linux has an inode number (e.g. `12345` in `/proc/net/tcp`). 

If you list the process descriptors:
```bash
PID=$(pgrep multi_listen)
ls -l /proc/$PID/fd/
```
You will see:
```text
lrwx------ 1 root root 64 Jun 21 21:15 3 -> socket:[12345]
lrwx------ 1 root root 64 Jun 21 21:15 4 -> socket:[12346]
```
The inode numbers link `/proc/net/tcp` entries directly to the program's file descriptors.

---

## 💡 The Moment

> [!TIP]
> **The Portals of the Mind:**
> Ports are not physical sockets or hardware slots on your machine. They are simply integer indices in the kernel's dispatch table. The kernel acts as the master dispatch clerk, matching the port in the incoming envelope against open descriptors to wake up the correct process. Ports are a partition of attention, allowing a single logical address to host many minds.

---

## Break It

What happens if two processes fight to sit at the same desk?

1. While `multi_listen` is running in Terminal 1, try to start a netcat listener on the HTTP port (80) in Terminal 2:
   ```bash
   nc -l -p 80
   ```
2. Watch it fail:
   ```text
   nc: Address already in use
   ```
3. The kernel blocks the `bind()` system call because a socket (`fd=3`) is already registered for port 80. Only one program can occupy a desk at a time.

---

## What You Can Do Now

- You can map processes to ports using `ss -tlnp`.
- You can decode raw kernel port tables in `/proc/net/tcp`.
- You can write a single C program that listens on multiple ports simultaneously.

---

## The New Problem

We can now route packets to the correct machine, and dispatch them to the correct process inside that machine using ports.

But the physical wire is drafty. Electrical signals get corrupted, and switches drop packets when they get overloaded. If you transfer a 100-page manuscript, and 30 pages vanish, the message is lost.

How do we guarantee that every page of our conversation arrives intact, and in the correct order, on an unreliable wire?

**[Next: Act IV, Question 10 → The Registered Mail](../10-the-registered-mail/)**
