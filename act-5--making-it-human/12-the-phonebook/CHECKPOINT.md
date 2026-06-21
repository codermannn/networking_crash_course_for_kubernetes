# Checkpoint: Module 12 · The Phonebook

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What does the kernel know about domain names like `google.com`?
*Explain what a network system call like `connect()` expects. Does it accept names, or is it completely blind to them? Who actually does the translation?*

---

### 2. What is `/etc/resolv.conf`, and what happens if you delete it?
*Why does running `curl 142.250.190.46` still work after deleting the file, but `curl google.com` fails? What does this tell you about name resolution vs. routing?*

---

### 3. Explain the difference between a Recursive DNS Resolver and an Authoritative DNS Server.
*Use the phonebook chain analogy. If you ask a local clerk for a number, and he doesn't know, how does he traverse the chain of phonebooks (Root → TLD → Domain)?*

---

### 4. How does Kubernetes use DNS for service discovery?
*Connect to K8s. When a pod curls `http://my-service`, what DNS nameserver is it querying? How does CoreDNS know the IP of the service?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you have mastered DNS. You are ready to tackle the final module: how we share a single public IP using a Con Artist!
