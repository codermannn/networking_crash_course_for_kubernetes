# Act II: The Crowded Hallway · How do we ignore the noise?

> **You are here:** Act II · Question 3 of 13
> **Time:** ~20 minutes
> **Tools you'll meet:** `tcpdump -e`, `ethtool`, `ip link`
> **Prerequisites:** [Module 02: The Fake Tray](../02-the-fake-tray/)

---

## The Situation

Imagine a long corridor where ten rooms sit side by side, all sharing the same physical hallway. There are no private telephone lines running between them. When `machine_a` wishes to speak to `machine_b`, it cannot whisper. It must shout its message directly into the shared air of the corridor.

Because the hallway is shared, the electrical ripples of that shout travel past the door of every single room. They enter the ears of `machine_c`, `machine_d`, and all the rest. 

If every room receives the vibration, how does `machine_c` know to ignore it? Why doesn't `machine_c`'s consciousness get cluttered with the messages flowing between A and B? How do we filter out the noise of the collective hallway to maintain the illusion of private conversation?

We must look at the hardware envelope.

---

## Your Prediction

> [!IMPORTANT]
> **Before running any commands, pause and reflect:**
> If we start a packet sniffer (`tcpdump`) on `machine_c` and send a message from `machine_a` to `machine_b`, will `machine_c`'s physical network card receive the raw electrical signals? If it does, why doesn't this conversation show up in `machine_c`'s normal applications?

---

## The Lab

Navigate to this directory and start your environment:

```bash
cd act-2--the-crowded-hallway/03-the-serial-number/lab
docker compose down
docker compose up -d
```

Open three terminal windows:
- **Terminal 1** (`machine_a`):
  ```bash
  docker exec -it mac_machine_a bash
  ```
- **Terminal 2** (`machine_b`):
  ```bash
  docker exec -it mac_machine_b bash
  ```
- **Terminal 3** (`machine_c`):
  ```bash
  docker exec -it mac_machine_c bash
  ```

---

## The Investigation

Let's inspect our physical identifiers. In Linux, these are called **MAC Addresses** (Media Access Control addresses). They are the raw, unchangeable signatures of the physical interfaces.

### Step 1: Read Your Own Serial Number

In Terminal 1 (`machine_a`), check your hardware serial number:

**Run this:**
```bash
cat /sys/class/net/eth0/address
```

**What to look for:**
A string of 6 hex bytes separated by colons, e.g., `02:42:ac:14:00:02`.

**What it means:**
This is your interface's MAC address—the serial number stamped on your room's mail slot. In the physical realm, no other interface in the world should share this exact label.

---

### Step 2: Read B's Serial Number

In Terminal 2 (`machine_b`), read its serial number:

**Run this:**
```bash
cat /sys/class/net/eth0/address
```
Note the MAC address of `machine_b`. Let's assume it is `02:42:ac:14:00:03`.

---

### Step 3: Sniff the Hallway from Machine C

In Terminal 3 (`machine_c`), let's listen to the hallway. We will run `tcpdump` with the `-e` flag, which forces the tool to show the hardware envelopes rather than just the logical letters inside:

**Run this:**
```bash
tcpdump -i eth0 -e icmp
```

**What to look for:**
It will start listening, quiet and receptive. Leave it running.

---

### Step 4: Yell from A to B

In Terminal 1 (`machine_a`), send a ping to `machine_b` (`172.20.0.3`):

**Run this:**
```bash
ping -c 1 172.20.0.3
```

Now, look at Terminal 3 (`machine_c`) where `tcpdump` is running. You should see output like:

```text
21:10:00.123456 02:42:ac:14:00:02 > 02:42:ac:14:00:03, ethertype IPv4 (0x0800), length 98: 172.20.0.2 > 172.20.0.3: ICMP echo request, id 1, seq 1, length 64
```

**What it means:**
1. Even though the message was meant for B, **Machine C's physical card heard the vibration**. The signal traveled to everyone.
2. The `-e` flag exposes the hardware envelope: `02:42:ac:14:00:02 > 02:42:ac:14:00:03`.
3. Normally, `machine_c`'s network card (NIC) reads the destination field (`02:42:ac:14:00:03`), compares it to its own ID (`02:42:ac:14:00:04`), realizes the mail is not for its temple, and silently drops it in hardware. 
4. The CPU of Machine C remains completely untouched. But because we ran `tcpdump`, we placed the card into **Promiscuous Mode**—an open, undifferentiated state of attention where it passes everything it hears up to the OS.

---

### Step 5: Inspecting Virtual Hardware

Let's use `ethtool` to inspect our network interface card (NIC):

**Run this:**
```bash
ethtool -i eth0
```

**What to look for:**
The driver field should show `veth`.

**What it means:**
`veth` stands for Virtual Ethernet. In this simulated world, the kernel is acting as the grand engineer, presenting a virtual device that behaves exactly like physical silicon, matching MAC addresses in software registers.

---

## The Evidence

You can check the MAC address mapping using the `ip link` command:

```bash
ip link show eth0
```
Look at the `link/ether` line:
```text
link/ether 02:42:ac:14:00:02 brd ff:ff:ff:ff:ff:ff
```
The `ff:ff:ff:ff:ff:ff` is the **Broadcast MAC address**—the universal sign that means "this message is for everyone who can hear it."

---

## 💡 The Moment

> [!TIP]
> **The Filter of Attention:**
> An IP address is a logical abstraction. But the physical wire doesn't understand abstractions; it only understands hardware channels. To send a packet, the kernel must wrap it in an Ethernet frame stamped with the destination's MAC address. The network card acts as a filter of attention, discarding the irrelevant noise of the universe before the computer's CPU is ever bothered.

---

## Break It

What happens if we duplicate a MAC address? Let's spoof `machine_c`'s MAC address to match `machine_b`'s address (`02:42:ac:14:00:03`).

In Terminal 3 (`machine_c`), change your MAC address:

```bash
ip link set dev eth0 down
ip link set dev eth0 address 02:42:ac:14:00:03
ip link set dev eth0 up
```

Now, in Terminal 1 (`machine_a`), send a ping to `machine_b` again:
```bash
ping -c 3 172.20.0.3
```

Watch the terminal outputs. Both B and C are on the bridge, and both now match the destination MAC address.
- Do both reply? Yes! The ping output in Terminal 1 will show duplicate responses (`DUP!`).
- The network switch (the docker bridge) is now thoroughly confused, sending packets to both slots. You have successfully hijacked traffic.

---

## What You Can Do Now

- You can explain how MAC addresses filter network noise at the hardware level.
- You can explain Promiscuous Mode and use `tcpdump -e` to read Ethernet frames.
- You can change (spoof) MAC addresses to intercept local network traffic.

---

## The New Problem

We now understand how the envelope is filtered. But there is a catch. When you write code, you only know the logical IP address of `machine_b` (`172.20.0.3`). You have no idea what physical MAC address is stamped on its network card. You just spun this container up!

If the network card cannot send a packet without a MAC address, how does the kernel bridge the gap between the logical IP address and the physical card it has never met?

**[Next: Act II, Question 4 → The Shout](../04-the-shout/)**
