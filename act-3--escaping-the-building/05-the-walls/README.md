# Act III: Escaping the Building · How do we stop everyone from shouting?

> **You are here:** Act III · Question 5 of 13
> **Time:** ~25 minutes
> **Tools you'll meet:** `ip netns`, `ip link add type veth`
> **Prerequisites:** [Module 04: The Shout](../../act-2--the-crowded-hallway/04-the-shout/)

---

## The Situation

In the previous act, we saw that when a container pings a new neighbor, it screams an ARP broadcast packet that reaches every network card in the hallway.

If you gather ten thousand computers sharing the same physical wire, the constant, deafening storm of broadcast shouting will choke the entire network. Nobody can hear anything over the collective din.

To restore peace and order, we must build **walls** to partition the hallway into soundproof chambers. In the world of Linux, these rooms are called **Network Namespaces**. 

We will create two isolated rooms (`room_a` and `room_b`) on the same computer, connect them with a virtual Ethernet thread (`veth` pair), and see if the namespace walls can successfully trap the shouts.

---

## Your Prediction

> [!IMPORTANT]
> **Before running any commands, pause and reflect:**
> If we create two network namespaces, connect them with a virtual cable, and scream an ARP broadcast inside Room A, will the broadcast emerge in Room B? Or do the namespace walls block broadcast signals?

---

## The Lab

Start the privileged lab workbench:

```bash
cd act-3--escaping-the-building/05-the-walls/lab
docker compose down
docker compose up -d
docker compose exec workbench bash
```

You are now inside the workbench container, which is running with the `privileged: true` flag.

---

## The Investigation

Let's build our isolated rooms and wire them up.

### Step 1: Witness the Permission Error (The Building Manager Key)

Before using our privileged shell, let's understand why we need it. 

If you run a container normally (without `--privileged`), you are a regular tenant. If you try to build a room, the kernel stops you.

Let's test this in a non-privileged shell. Exit the workbench container or open a new terminal on your host machine, and run:

```bash
docker run --rm nicolaka/netshoot ip netns add room_test
```

**What to look for:**
It fails with:
```text
Cannot create namespace directory "/var/run/netns": Permission denied
```
Or:
```text
mount --make-shared / failed: Operation not permitted
```

**What it means:**
Creating namespaces modifies the kernel's partition table. By default, Docker blocks containers from doing this to protect the host. To perform kernel-level networking modifications, we must run with `privileged: true` (which hands the container the building manager's master key).

Make sure you are back inside your privileged `docker compose exec workbench bash` shell before proceeding.

---

### Step 2: Build the Soundproof Rooms

Let's create two isolated rooms: `room_a` and `room_b`.

**Run this:**
```bash
ip netns add room_a
ip netns add room_b
```

Verify they exist:
```bash
ip netns list
```

**What to look for:**
You should see:
```text
room_b
room_a
```

**What it means:**
We have created two fully isolated network stacks. Each room has its own loopback interface, its own routing table, and its own set of devices. They are completely soundproofed from each other and from the host.

---

### Step 3: Build the Hallway (Veth Pair)

Now, let's create a virtual Ethernet cable. Think of this as a double-sided cable. If you write bytes into one end, they emerge from the other end.

**Run this:**
```bash
ip link add veth_a type veth peer name veth_b
```

Check your host interfaces:
```bash
ip link show
```

**What to look for:**
You will see `veth_a` and `veth_b` listed in your host namespace.

**What it means:**
We created a virtual Ethernet link (a `veth` pair). Currently, both endpoints are lying in the building's lobby (the host namespace).

---

### Step 4: Thread the Cable Into the Rooms

Let's push `veth_a` into `room_a`, and `veth_b` into `room_b`.

**Run this:**
```bash
ip link set veth_a netns room_a
ip link set veth_b netns room_b
```

Check your host interfaces again:
```bash
ip link show
```

**What to look for:**
`veth_a` and `veth_b` have vanished from the host interface list!

**What it means:**
The host namespace can no longer see them. They have been moved inside the isolated rooms.

---

### Step 5: Start the Interfaces

By default, any new interface is created in the "down" state (disconnected). We must go inside each room and turn the interface on.

**Run this:**
```bash
ip netns exec room_a ip link set dev veth_a up
ip netns exec room_b ip link set dev veth_b up
```

---

### Step 6: Scream inside Room A

Let's test our soundproofing. We will listen in Room B and scream in Room A.

1. Open a **second terminal window** on your host, exec back into the workbench container:
   ```bash
   docker exec -it walls_workbench bash
   ```
2. In Terminal 2, enter Room B and start listening for broadcasts:
   ```bash
   ip netns exec room_b tcpdump -i veth_b arp
   ```
3. In Terminal 1, enter Room A and scream a broadcast message (we will ping a dummy IP to force an ARP shout):
   ```bash
   ip netns exec room_a arping -I veth_a -c 3 10.0.0.2
   ```

Look at Terminal 2. Did `tcpdump` capture the shouts?

**What to look for:**
Terminal 2 prints:
```text
0 packets captured
0 packets received by filter
```

**What it means:**
The shouts were captured inside Room A, but they did **not** emerge in Room B! 
Even though they are connected by a virtual cable, the interfaces do not have IP addresses or active routes. The broadcast domain is restricted to the namespace. The walls successfully stopped the screaming from flooding the network.

---

## The Evidence

The definitive proof of network isolation is in the proc filesystem. Every process in Linux points to its namespace file.

Let's list the namespace inodes:

```bash
ls -l /proc/self/ns/net
```
Note the inode number, e.g. `net:[4026531992]`.

Now, run it inside `room_a`'s context:

```bash
ip netns exec room_a ls -l /proc/self/ns/net
```
You will see a different inode number, e.g. `net:[4026532250]`.

The kernel maintains different namespace objects in memory. The process inside `room_a` is locked into a separate file descriptor mapping for all networking operations.

---

## 💡 The Moment

> [!TIP]
> **The Partition of Perception:**
> Docker does not use hypervisors or VM hardware to isolate container networks. It simply calls the `CLONE_NEWNET` flag during process creation to allocate a new network namespace inode. Container isolation is just filesystem partition magic at the kernel level. What looks like physical isolation is simply a division of the kernel's perception.

---

## Break It

What happens if we move both endpoints of the virtual Ethernet cable back into the same room?

1. Move `veth_b` out of `room_b` and into `room_a`:
   ```bash
   ip netns exec room_b ip link set veth_b netns room_a
   ```
2. Verify they are both inside `room_a`:
   ```bash
   ip netns exec room_a ip link show
   ```
3. Start listening in Terminal 2 on `veth_b` (now inside `room_a`):
   ```bash
   ip netns exec room_a tcpdump -i veth_b arp
   ```
4. Scream in Terminal 1 on `veth_a`:
   ```bash
   ip netns exec room_a arping -I veth_a -c 1 10.0.0.2
   ```
   Now, Terminal 2 prints the packet capture! The wall was bypassed because both ends of the wire reside in the same room.

---

## What You Can Do Now

- You can create, list, and execute commands inside Linux Network Namespaces (`ip netns`).
- You can create `veth` pairs to wire up isolated namespaces.
- You can explain how Docker isolates container networking at the kernel level.

---

## The New Problem

We built walls to trap broadcast noise. 

But now we have a new problem. Room A and Room B are completely cut off. When Room A screams for Room B's hardware MAC address, the broadcast is trapped inside Room A. They cannot discover each other, and they cannot talk.

We need to assign **Room Numbers** (IP addresses) to identify which floor each room is on, so we can route messages between them.

**[Next: Act III, Question 6 → The Room Number](../06-the-room-number/)**
