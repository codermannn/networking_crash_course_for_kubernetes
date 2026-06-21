# Checkpoint: Module 07 · The Map

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What is a Default Gateway (Gateway of Last Resort)?
*Explain the building's front door analogy. If the kernel's routing table has no specific match for an IP, where does it send the packet?*

---

### 2. How does `traceroute` discover the IPs of intermediate routers?
*Explain the TTL (Time to Live) mechanism. How does the kernel use deliberately short lifespans and the router's "death notification" (ICMP Time Exceeded) to map the road?*

---

### 3. What information is stored in `/proc/net/route`, and why is it represented in hexadecimal?
*Explain how the kernel reads this file in memory. What does `00000000` represent for a destination, and what does it mean?*

---

### 4. When a router forwards a packet from Room A to Room B, does it change the Destination IP?
*If it doesn't change the Destination IP, what *does* it change on the envelope to get it across the physical hallway? (Think MAC addresses).*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you have mastered routing tables. You are ready to discuss how the internet scales this dynamically!
