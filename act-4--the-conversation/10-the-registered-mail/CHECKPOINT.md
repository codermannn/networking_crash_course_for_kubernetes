# Checkpoint: Module 10 · The Registered Mail

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What are the three steps of the TCP Handshake?
*Use the business greeting analogy. What do SYN, SYN-ACK, and ACK stand for, and why does the handshake require exactly three steps instead of two?*

---

### 2. How does TCP guarantee that data arrives complete and in order on a wire that drops 30% of packets?
*Explain the mechanism of Sequence Numbers and Acknowledgments (ACKs). What does the receiver write on the confirmation slip?*

---

### 3. What is a Duplicate ACK, and what does it tell the sender?
*If the sender receives four ACKs all asking for page 5, what does the kernel do? What is "Fast Retransmit"?*

---

### 4. Why does configuring packet loss with `tc` require `--cap-add=NET_ADMIN`?
*Connect to permissions. Why doesn't the OS allow a normal container to run `tc`? What is the danger of letting any tenant touch the queue scheduler?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you understand TCP mechanics. You are ready to explore the paper airplane alternative: UDP!
