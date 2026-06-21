# Checkpoint: Module 03 · The Serial Number

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What does the `-e` flag on `tcpdump` do, and why does the default view hide this information?
*If a colleague says: "I ran tcpdump but I don't see any hardware information," what are they missing? What layer is hidden by default?*

---

### 2. How does a network card (NIC) decide whether to process an incoming packet or discard it?
*Describe the mail slot metaphor. What two values does the NIC compare before it decides to wake up the OS kernel?*

---

### 3. What happens to the network when two machines share the exact same MAC address?
*Describe the chaos in the hallway. Who gets the mail? Does it load-balance, go to both, or cause packet loss?*

---

### 4. Where in the Linux filesystem can you find the MAC address of an interface without using any net tools?
*How does this fit into the "Everything is a File" philosophy?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you have mastered MAC filtering. Let's move on to the next problem: how do we discover these serial numbers in the first place?
