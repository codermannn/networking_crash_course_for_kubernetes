# Checkpoint: Module 04 · The Shout

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What triggers an ARP request? Why doesn't the kernel send one for every single packet?
*Explain the role of the kernel's neighbor cache. How long do entries live, and why do we cache them?*

---

### 2. What is the Broadcast MAC address (`ff:ff:ff:ff:ff:ff`), and how does a network switch handle it differently than a unicast address?
*Use the "hallway shout" metaphor. Who is forced to open and read a broadcast envelope?*

---

### 3. If you configure a wrong static ARP entry for a machine's IP, what happens to your traffic?
*Why does the ping fail immediately without sending any packets on the wire? Where does the letter go?*

---

### 4. How can an attacker on the same local network use ARP to sniff all your traffic?
*Explain "ARP Spoofing" (or poisoning) using the mail clerk analogy. How do they trick your notebook?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you have mastered local discovery. You are ready to face the next big boss: what happens when the hallway is too big, and we need to build walls?
