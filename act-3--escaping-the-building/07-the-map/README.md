# Act III: Escaping the Building · How does the mail clerk know where to send mail?

> **You are here:** Act III · Question 7 of 13
> **Time:** ~25 minutes
> **Tools you'll meet:** `/proc/net/route` (hex decoding), `ip route add`, `traceroute`
> **Prerequisites:** [Module 06: The Room Number](../06-the-room-number/)

---

## The Situation

In the previous module, we saw that if we assign Room A the IP `10.0.1.1` (Floor 1) and Room B `10.0.2.1` (Floor 2), they cannot talk. The kernel refuses to send packets because it doesn't have a map for the other floor.

To connect them, we need to build a **Routing Map** and introduce a **Router**—a mail clerk sitting at the intersection of hallways.

We will set up a three-room topology inside our workbench:
- `room_a` (`10.0.1.1` / Floor 1)
- `router` (acting as a mail clerk, connected to both Floor 1 and Floor 2)
- `room_b` (`10.0.2.1` / Floor 2)

Let's see how the kernel uses its map to route letters through the clerk.

---

## Your Prediction

> [!IMPORTANT]
> **Before running any commands, pause and reflect:**
> When a router forwards a packet from `room_a` to `room_b`, does it rewrite the destination IP address on the letter? If not, what changes on the hardware envelope to ensure the packet goes to the router first, and then to the final room?

---

## The Lab

Start the privileged workbench:

```bash
cd act-3--escaping-the-building/07-the-map/lab
docker compose down
docker compose up -d
docker compose exec workbench bash
```

Let's build the three rooms, wire them up, and assign IP addresses. Run this setup script in your workbench shell:

```bash
# 1. Create rooms and router namespaces
ip netns add room_a
ip netns add room_b
ip netns add router

# 2. Create the hallways (veth pairs)
ip link add veth_a type veth peer name veth_ar
ip link add veth_b type veth peer name veth_br

# 3. Thread the cables
ip link set veth_a netns room_a
ip link set veth_ar netns router
ip link set veth_b netns room_b
ip link set veth_br netns router

# 4. Turn the links on
ip netns exec room_a ip link set dev veth_a up
ip netns exec router ip link set dev veth_ar up
ip netns exec room_b ip link set dev veth_b up
ip netns exec router ip link set dev veth_br up

# 5. Assign Room IPs
ip netns exec room_a ip addr add 10.0.1.1/24 dev veth_a
ip netns exec room_b ip addr add 10.0.2.1/24 dev veth_b

# 6. Assign Router IPs (Router has one mail slot on each floor)
ip netns exec router ip addr add 10.0.1.254/24 dev veth_ar
ip netns exec router ip addr add 10.0.2.254/24 dev veth_br
```

---

## The Investigation

Let's verify if they can talk. Ping the router from `room_a`:
```bash
ip netns exec room_a ping -c 1 10.0.1.254
```
This works because `10.0.1.254` is on the local floor.

Now, try to ping `room_b` (`10.0.2.1`) from `room_a`:
```bash
ip netns exec room_a ping -c 1 10.0.2.1
```
It fails with `Network is unreachable`. The map is missing.

---

### Step 1: Tell the Router to Forward Packets

By default, Linux network stacks behave like hosts, not routers. If a host receives a packet whose destination MAC is theirs but whose destination IP is NOT theirs, it throws it in the trash.

We must tell our router namespace to act as a mail clerk and forward these packets.

**Run this:**
```bash
ip netns exec router sysctl -w net.ipv4.ip_forward=1
```

**What to look for:**
It prints `net.ipv4.ip_forward = 1`.

**What it means:**
We gave the router permission to forward mail. It will now inspect the routing table of the router namespace to decide where to forward packets.

---

### Step 2: Add Maps to the Rooms

`room_a` still doesn't know how to reach Floor 2. We must tell it: *"To reach floor 10.0.2.0/24, hand the packet to the clerk at 10.0.1.254."*

**Run this:**
```bash
ip netns exec room_a ip route add 10.0.2.0/24 via 10.0.1.254 dev veth_a
ip netns exec room_b ip route add 10.0.1.0/24 via 10.0.2.254 dev veth_b
```

Now, try the ping again:
```bash
ip netns exec room_a ping -c 1 10.0.2.1
```

**What to look for:**
It works!
```text
1 packets transmitted, 1 received, 0% packet loss, time 0ms
```

**What it means:**
The packet successfully traveled from `room_a` to the `router`, was forwarded to `room_b`, and the reply took the reverse path back.

---

### Step 3: Read the Kernel's Handwriting in Hex

Let's read the raw map the kernel uses.

**Run this:**
```bash
ip netns exec room_a cat /proc/net/route
```

**What to look for:**
A table containing hex values:
```text
Iface   Destination Gateway     Flags   RefCnt  Use Metric  Mask            MTU     Window  IRTT
veth_a  0002000A    FE01000A    0003    0       0   0       00FFFFFF        0       0       0
```

**What it means:**
Let's decode this hex!
- `Destination`: `0002000A`. Linux stores IP addresses in network byte order (little-endian hex).
  - Break it down into bytes: `0A` `00` `02` `00`.
  - Convert to decimal: `0A` = 10, `00` = 0, `02` = 2, `00` = 0.
  - This is `10.0.2.0`!
- `Gateway`: `FE01000A`. 
  - Bytes: `0A` `00` `01` `FE`.
  - Decimal: `0A` = 10, `00` = 0, `01` = 1, `FE` = 254.
  - This is `10.0.1.254`!
- `Mask`: `00FFFFFF`.
  - Bytes: `FF` `FF` `FF` `00`.
  - Decimal: `255.255.255.0`.
  - This is our `/24` subnet mask!

The kernel reads this raw memory array to make microsecond routing decisions.

---

### Step 4: Tracing the Hops

Let's verify the hops using `traceroute` from `room_a`:

**Run this:**
```bash
ip netns exec room_a traceroute -n 10.0.2.1
```

**What to look for:**
You should see:
```text
1  10.0.1.254  0.035 ms
2  10.0.2.1  0.032 ms
```

**What it means:**
The packet went through hop 1 (the router at `10.0.1.254`) before reaching hop 2 (the target at `10.0.2.1`). 
`traceroute` does this by sending a packet with a **Time-To-Live (TTL) of 1**. The router decrements it to `0` (interpreting it as a packet that has run out of breath), drops it, and sends an ICMP "Time Exceeded" reply, revealing its IP. `traceroute` then sends a packet with TTL 2, mapping the next hop, and so on.

---

## The Evidence

Let's prove the router rewrites the MAC envelope but leaves the IP envelope intact.

1. Start `tcpdump` inside `room_b` showing MAC headers:
   ```bash
   ip netns exec room_b tcpdump -i veth_b -e -n
   ```
2. Ping `10.0.2.1` from `room_a` again:
   ```bash
   ip netns exec room_a ping -c 1 10.0.2.1
   ```
3. Look at `tcpdump` output:
   ```text
   02:42:ac:14:XX:XX > 02:42:ac:14:YY:YY ... 10.0.1.1 > 10.0.2.1: ICMP echo request
   ```
   The source MAC is the router's interface `veth_br` MAC, but the source IP remains `10.0.1.1`. The router crossed out the hardware serial numbers on the outside envelope, but left the inner letter's address untouched.

---

## 💡 The Moment

> [!TIP]
> **The Local Wrapper and the Global Destination:**
> Routers do not alter the destination IP of your packets. They do not rewrite the name on the letter. They merely peel off the local Ethernet MAC envelope, consult their internal map, and wrap the letter in a new local MAC envelope for the next hop. IPs are global and eternal; MACs are local and transient. The journey changes at every step, but the final destination remains one.

---

## Break It

What happens if we break the path of return?

1. Delete the return route inside `room_b`:
   ```bash
   ip netns exec room_b ip route del 10.0.1.0/24
   ```
2. Try the ping from `room_a`:
   ```bash
   ip netns exec room_a ping -c 1 10.0.2.1
   ```
   It fails. The request reached `room_b` (you can verify this with the `tcpdump` in B), but `room_b` had no map to send the reply back to Floor 1. In networking, as in dialogue, paths must be complete in both directions for communication to exist.

---

## What You Can Do Now

- You can read and manually decode raw routing tables in `/proc/net/route`.
- You can add static routes and configure a Linux namespace to forward packets as a router.
- You can explain how `traceroute` uses TTL limits to map hops.

---

## The New Problem

We manually configured 3 routes. 

But there are nearly a million active subnets on the global internet. No human can type a million static `ip route add` commands, nor can they react in milliseconds when a wire snaps in Denver. 

The mail clerks (routers) of the world need a way to gossip with each other to automatically learn the map of the world.

**[Next: Act III, Question 8 → The Gossip](../08-the-gossip/)**
