# Checkpoint: Module 09 · The Desk Number

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What is a port?
*Use the room desk metaphor. If the IP address gets you to the door of the room, what does the port number get you inside the room?*

---

### 2. How does the kernel route an incoming packet to the correct process when multiple processes are running on the same IP address?
*Explain what a Socket represents in the kernel. What properties (specifically, the 4-tuple) does it check on the incoming packet?*

---

### 3. What does "Address already in use" mean?
*Why can't two programs bind to the exact same port on the same IP? What is the analogy of two people fighting for the same desk?*

---

### 4. How do you decode a port from `/proc/net/tcp`?
*If the local address field shows `00000000:01BB`, what IP and port does this represent? Convert `01BB` from hex to decimal.*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you understand ports. You are ready to learn how to keep the conversation reliable when the hallway is drafty and packets drop!
