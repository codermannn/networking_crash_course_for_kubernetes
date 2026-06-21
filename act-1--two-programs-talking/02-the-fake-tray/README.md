# Act I: Two Programs Talking · What if they're in different buildings?

> **You are here:** Act I · Question 2 of 13
> **Time:** ~20 minutes
> **Tools you'll meet:** `nc`, `strace` (socket filters), `ls -l /proc/<PID>/fd/`
> **Prerequisites:** [Module 01: The Tray](../01-the-tray/)

---

## The Situation

In the previous module, we found a way to share a single thought between two isolated minds by using a Named Pipe—a local tray where bytes were placed in memory. It was a beautiful, brief bridge, but it relied entirely on the illusion of a shared floor. They both had to be sitting in the same room, reaching for the exact same spot on the table, `/tmp/my_tray`.

But what if the two minds are in completely different temples? What if one process is running on `machine_a` and the other on `machine_b`? They do not share a filesystem. There is no `/tmp/my_tray` that both can touch. The physical separation seems absolute.

How do we pass a note across the abyss of the network? We must invite the kernel to perform a grand act of magic: to create a "fake tray" that looks and behaves exactly like a local file, but secretly transports the bytes across the ether.

---

## Your Prediction

> [!IMPORTANT]
> **Before running any commands, pause and reflect:**
> When a program writes bytes to a socket to communicate with a distant machine, does it know it is sending data over a network wire? Or is the kernel playing a game of masquerade, tricking the program into thinking it is still just writing to a simple, local file?

---

## The Lab

Let's clean up our old workbench and start our multi-machine sandbox:

```bash
cd act-1--two-programs-talking/02-the-fake-tray/lab
docker compose down
docker compose up -d
```

We now have two separate containers running: `machine_a` (the client) and `machine_b` (the server). 

Open two terminal windows.
- In **Terminal 1**, log into `machine_a`:
  ```bash
  docker exec -it machine_a bash
  ```
- In **Terminal 2**, log into `machine_b`:
  ```bash
  docker exec -it machine_b bash
  ```

---

## The Investigation

Let's compile our client and server programs.

In both Terminal 1 (`machine_a`) and Terminal 2 (`machine_b`), compile the programs:
```bash
gcc -o /lab/code/socket_hello /lab/code/socket_hello.c
gcc -o /lab/code/socket_listen /lab/code/socket_listen.c
```

### Step 1: Start the Listener (The Server)

In Terminal 2 (`machine_b`), start the listening program and trace its system calls:

**Run this:**
```bash
strace -e socket,bind,listen,accept /lab/code/socket_listen
```

**What to look for:**
The program output shows:
```text
socket(AF_INET, SOCK_STREAM, IPPROTO_IP) = 3
bind(3, {sa_family=AF_INET, sin_port=htons(8080), sin_addr=inet_addr("0.0.0.0")}, 16) = 0
listen(3, 3)                            = 0
Listening on port 8080... (blocking until someone connects)
accept(3,
```

And it stops there, waiting.

**What it means:**
1. `socket()` tells the kernel: "Create a new network portal." The kernel returns file descriptor `3`.
2. `bind()` anchors this portal to port `8080` (a specific door on the outside wall).
3. `listen()` prepares the kernel to queue incoming guests.
4. `accept()` tells the kernel to put the process to sleep until a guest actually knocks on descriptor `3`.

---

### Step 2: Retrieve the IP of the Server

We need the network address of `machine_b` so `machine_a` knows where to send its message.

In a new terminal window (or inside `machine_b`'s shell if you open a new prompt), run:
```bash
ip addr show eth0
```
Look for the `inet` line. Let's assume it is `172.20.0.3` (your actual IP may vary, e.g., `172.18.0.3`). Let's use whatever IP is printed.

---

### Step 3: Connect and Send the Message

In Terminal 1 (`machine_a`), run the client program using `strace` to connect to `machine_b` (replace `172.20.0.3` with the actual IP you found):

**Run this:**
```bash
strace -e socket,connect /lab/code/socket_hello 172.20.0.3 "Hello from Machine A!"
```

**What to look for:**
The trace shows:
```text
socket(AF_INET, SOCK_STREAM, IPPROTO_IP) = 3
Connecting to 172.20.0.3:8080... (blocking)
connect(3, {sa_family=AF_INET, sin_port=htons(8080), sin_addr=inet_addr("172.20.0.3")}, 16) = 0
Sending message: 'Hello from Machine A!'
+++ exited with 0 +++
```

Now look at Terminal 2 (`machine_b`). The server has woken up and printed:
```text
Connection accepted from 172.20.0.2
Received message: 'Hello from Machine A!'
```

---

## The Evidence

The magic is in how the kernel represents this socket to the program. Let's start the server in Terminal 2 again, but without `strace` so it keeps running:

```bash
/lab/code/socket_listen
```

While it is waiting, run this command in a new terminal window (inside the server container `machine_b`):

```bash
PID=$(pgrep socket_listen)
ls -l /proc/$PID/fd/
```

You will see:
```text
lrwx------ 1 root root 64 Jun 21 21:05 3 -> socket:[23456]
```

**What it means:**
File Descriptor `3` points to a `socket` object inside the kernel. 
The program `socket_listen.c` calls `read(new_socket, buffer, sizeof(buffer))` where `new_socket` is just integer `4`!
The code uses the exact same `read()` and `write()` calls it used for Named Pipes. It has no idea it is talking to a network card. The OS kernel is running a giant simulation, masking the network card as a file descriptor.

---

## 💡 The Moment

> [!TIP]
> **The Great Masquerade:**
> Sockets are simply file descriptors wearing a mask. When a program writes to descriptor `3`, it is blissfully unaware of the vast distance the packet must travel. Whether it is a local named pipe, a file on a disk, or a machine across the ocean, the program uses the exact same interface. The kernel acts as the grand illusionist, presenting the entire world as if it were a single, local filing cabinet.

---

## Break It

What happens if we dissolve the listening program, and the client still tries to connect?

1. Stop your server program if it is running in Terminal 2 (Ctrl+C).
2. Run the client program in Terminal 1:
   ```bash
   /lab/code/socket_hello 172.20.0.3 "Hello again!"
   ```
3. Watch the error returned:
   ```text
   connect: Connection refused
   ```
4. Run it with `strace` to see the kernel's actual response code:
   ```bash
   strace -e connect /lab/code/socket_hello 172.20.0.3 "Hello again!"
   ```
   You will see:
   ```text
   connect(3, ..., 16) = -1 ECONNREFUSED (Connection refused)
   ```
   The client kernel received an explicit packet from the server kernel saying: "No one is sitting at port 8080. Drop dead." The socket interface returns `ECONNREFUSED` up to userspace.

---

## What You Can Do Now

- You can explain how TCP clients and servers establish connections using the Socket API.
- You can trace socket creation, binding, and listening syscalls.
- You can prove that sockets are just standard File Descriptors in Linux.

---

## The New Problem

We can now talk across the wire! 

But imagine we add 8 more containers to our network. They are all sharing a single virtual bridge network—plugged into the same virtual ethernet switch. 

When `machine_a` sends a packet to `machine_b`, the electrical signals travel down the wire to *everyone*. How does `machine_c` know to ignore it? How does `machine_b` know it is for them? How do we label the envelope?

**[Next: Act II, Question 3 → The Serial Number](../../act-2--the-crowded-hallway/03-the-serial-number/)**
