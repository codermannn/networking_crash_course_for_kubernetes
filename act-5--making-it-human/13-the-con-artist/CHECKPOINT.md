# Checkpoint: Module 13 · The Con Artist

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What is the role of the "Con Artist" (NAT) in a home or container network?
*Explain how five devices, all using private IPs like `192.168.1.X`, can browse the internet at the same time using a single public IP. What does the router do to the return address?*

---

### 2. What is the Connection Tracking table (`conntrack`), and why is it necessary for NAT?
*Explain what happens when the reply packet comes back from the website. How does the router know which private IP was the original sender?*

---

### 3. What happens if you run `conntrack -F` (flush the table) while active TCP transfers are running?
*Why does the transfer immediately freeze and die? What did the con artist lose that made him drop the return letters?*

---

### 4. How does Kubernetes Service routing use NAT?
*Connect to K8s. When a pod sends a request to a Service ClusterIP (`10.96.0.1`), how does kube-proxy use `iptables` to redirect the traffic to a real Pod IP (e.g. `10.244.1.5`)? Is this SNAT or DNAT?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, congratulations! You have finished the final module. You have completed the Networking Crash Course!
