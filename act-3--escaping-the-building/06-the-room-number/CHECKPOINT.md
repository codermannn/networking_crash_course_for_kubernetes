# Checkpoint: Module 06 · The Room Number

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What are the two parts of an IP address?
*Use the floor and room metaphor. How does the subnet mask serve as the "scissors" to separate these two parts?*

---

### 2. How does the OS kernel decide if a target IP address is on the same local network or a remote network?
*Explain the binary AND operation. What two results does the kernel compare before deciding to send an ARP shout?*

---

### 3. What does CIDR notation (like `/24` or `/16`) actually represent in binary?
*Explain why a `/24` network has 254 usable host addresses, while a `/25` has only 126. What happens to the other addresses?*

---

### 4. What is a Pod CIDR in Kubernetes?
*Connect to K8s. If a K8s node is allocated a Pod CIDR of `10.244.1.0/24`, what is the maximum number of pods that can run on that node? Why?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you understand IP routing logic. You are ready to build a routing table map!
