# Checkpoint: Module 05 · The Walls

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. What is a Linux Network Namespace?
*Use the soundproof room analogy. What properties does a process inherit when it runs inside a specific namespace compared to the host?*

---

### 2. How does a virtual Ethernet (`veth`) pair behave like a physical cable?
*If you write data to one end of a veth pair (`veth0`), where does it emerge? What is the kernel-level mechanism mapping the two interfaces?*

---

### 3. Why does creating a namespace fail inside a default Docker container without `--privileged`?
*Explain the building manager's master key metaphor. What capability does `--privileged` grant to the container process?*

---

### 4. How does Docker use namespaces and veth pairs every time you run a container?
*Peel back the curtain. If a user runs `docker run -d nginx`, what steps does Docker take behind the scenes to wire up that container?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you have mastered Linux network virtualization. You are ready to tackle the next issue: how do we assign room numbers to make this hallway functional?
