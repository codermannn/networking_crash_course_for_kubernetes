# Checkpoint: Module 11 · The Paper Airplane

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What does it mean that UDP is "connectionless"?
*Use the paper airplane analogy. If you throw a paper airplane out of the window, does it wait for the recipient to acknowledge they are ready? Does it track if it landed in a tree?*

---

### 2. Compare the packet overhead of TCP vs. UDP.
*If you send the 5-character string "Hello" using both protocols, how many total packets (handshakes, ACKs, FINs) fly across the wire for TCP? How many for UDP?*

---

### 3. What is Head-of-Line (HoL) Blocking, and how does UDP avoid it?
*If packet 2 gets lost in a 10-packet transfer, why does TCP freeze the delivery of packets 3-10? Why does UDP just deliver them anyway?*

---

### 4. Name three systems that run on UDP and explain why they prefer speed over safety.
*Why does DNS run on UDP? Why do multiplayer shooters (like Counter-Strike) use UDP for player coordinates?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you understand transport layers. You are ready for the final act: making this system usable for humans!
