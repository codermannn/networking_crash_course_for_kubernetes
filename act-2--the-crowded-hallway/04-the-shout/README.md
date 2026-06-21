# Act II: The Crowded Hallway · How do we find the hardware ID?

> **You are here:** Act II · Question 4 of 13
> **Time:** ~20 minutes
> **Tools you'll meet:** `ip neigh`, `tcpdump arp`
> **Prerequisites:** [Module 03: The Serial Number](../03-the-serial-number/)

---

## The Situation

In the previous module, we learned that the network card checks the destination MAC address on every Ethernet frame, filtering out messages meant for other rooms to keep the CPU quiet.

But this introduces a chicken-and-egg riddle.

When you write a program, you speak in the language of **IP addresses** (e.g., `172.20.0.3`). You do not know the physical signature—the MAC address—of the target machine. 

If the network card cannot send a single byte down the wire without a physical destination address, how does the kernel bridge this gap? How does it map the logical name to the physical form?

It must shout. It must ask the corridor.

---

## Your Prediction

> [!IMPORTANT]
> **Before running any commands, pause and reflect:**
> When you ping a brand new IP address, a tiny delay ripples through the first packet. What is the kernel doing in that split second? Is it consulting a central authority, or is it screaming in the hallway?

---

## The Lab

Start your environment:

```bash
cd act-2--the-crowded-hallway/04-the-shout/lab
docker compose down
docker compose up -d
```

Open two terminal windows:
- **Terminal 1** (`machine_a`):
  ```bash
  docker exec -it arp_machine_a bash
  ```
- **Terminal 2** (`machine_b`):
  ```bash
  docker exec -it arp_machine_b bash
  ```

---

## The Investigation

Let's look at the lookup table the kernel keeps in memory, called the **Neighbor Cache** or **ARP Table** (Address Resolution Protocol table). It is the kernel's pocket notebook of who lives where.

### Step 1: Read the Notebook (Neighbor Table)

In Terminal 1 (`machine_a`), check if the kernel knows about any neighbors:

**Run this:**
```bash
ip neigh
```

**What to look for:**
The command should return absolutely nothing.

**What it means:**
The kernel's neighbor cache is empty. It has no memory of what MAC addresses correspond to any IPs on the network. Its notebook is blank.

---

### Step 2: Start the Ear (tcpdump)

In Terminal 2 (`machine_b`), start listening specifically for ARP shouts:

**Run this:**
```bash
tcpdump -i eth0 arp -en
```

**What to look for:**
It will start listening. Leave it running.

---

### Step 3: Trigger the Ping

In Terminal 1 (`machine_a`), ping `machine_b` (`172.20.0.3`):

**Run this:**
```bash
ping -c 1 172.20.0.3
```

**What to look for:**
Look at Terminal 2 (`machine_b`) where `tcpdump` is running. You will see a broadcast packet fly past:

```text
21:15:00.123456 02:42:ac:14:00:02 > ff:ff:ff:ff:ff:ff, ethertype ARP (0x0806), length 42: Request who-has 172.20.0.3 tell 172.20.0.2, length 28
21:15:00.123500 02:42:ac:14:00:03 > 02:42:ac:14:00:02, ethertype ARP (0x0806), length 42: Reply 172.20.0.3 is-at 02:42:ac:14:00:03, length 28
```

**What it means:**
1. Machine A yelled to the broadcast address `ff:ff:ff:ff:ff:ff` (telling all network cards in the hallway: "Everyone open this envelope!").
2. The payload of the shout was: *"Who has IP 172.20.0.3? Tell 172.20.0.2!"*
3. Machine B heard it, recognized its own IP, and replied directly to A's MAC: *"I have it! My physical address is 02:42:ac:14:00:03."*

---

### Step 4: Check the Notebook Again

Now, in Terminal 1 (`machine_a`), check your neighbor table again:

**Run this:**
```bash
ip neigh
```

**What to look for:**
You should see:
```text
172.20.0.3 dev eth0 lladdr 02:42:ac:14:00:03 REACHABLE
```

**What it means:**
The kernel wrote the answer in its notebook (`ip neigh` cache). The next time you send data to `172.20.0.3`, it will bypass the shout completely and write the MAC address directly on the envelope.

---

## The Evidence

Let's prove the kernel doesn't shout if it already knows the answer. 

1. Keep `tcpdump arp` running in Terminal 2.
2. In Terminal 1, ping again:
   ```bash
   ping -c 1 172.20.0.3
   ```
3. Look at Terminal 2. Did `tcpdump` print any new ARP packets? No! The ping worked instantly, and no one shouted, because the kernel read the MAC address from its notebook cache.

---

## 💡 The Moment

> [!TIP]
> **The Collective Memory:**
> The local network is an incredibly loud room. Every time a computer needs to speak to a new logical address, it must yell a broadcast message to everyone: *"Who has this IP?"* We are saved from this deafening chaos only by the kernel's memory—the neighbor cache. The kernel remembers the shout, writing it in its notebook so it may walk in silence for the next few minutes.

---

## Break It

What happens if you feed the kernel a lie? Let's write a wrong MAC address in the notebook.

1. Flush the neighbor cache in Terminal 1:
   ```bash
   ip neigh flush all
   ```
2. Manually write a static entry pointing to a ghost MAC address:
   ```bash
   ip neigh replace 172.20.0.3 lladdr 00:00:00:00:00:09 dev eth0
   ```
3. Verify it is in the table:
   ```bash
   ip neigh
   ```
4. Now, ping `172.20.0.3` again:
   ```bash
   ping -c 1 172.20.0.3
   ```
   What happens? The ping fails immediately. Look at the `tcpdump` in Terminal 2. Did it print any ARP packets? No! 
   The kernel believed its notebook, wrote `00:00:00:00:00:09` on the envelope, and threw it down the hallway. Because no NIC matched that ghost address, the packet vanished. The kernel never shouted because it thought it already knew the answer.

---

## What You Can Do Now

- You can explain how ARP broadcasts map logical IP addresses to physical MAC addresses.
- You can inspect and flush the kernel neighbor cache (`ip neigh`).
- You can trace ARP requests and replies on the wire using `tcpdump arp`.

---

## The New Problem

Shouting in the hallway is great when there are 10 computers in a room. 

But what if there are 900,000 computers? If every computer shouts every time it wants to find a neighbor, the hallway drowns in noise. The network would collapse under the weight of "who-has" broadcasts.

We need to build **walls** to separate computers into soundproof rooms, and place a **mail clerk** at the door to route messages across walls.

**[Next: Act III, Question 5 → The Walls](../../act-3--escaping-the-building/05-the-walls/)**
