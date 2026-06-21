# Checkpoint: Module 02 · The Fake Tray

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. How does the Operating System pretend that a network connection is just a file?
*Explain what a "File Descriptor" is. How does a program write bytes to another computer on the internet without ever calling a "network send" system call?*

---

### 2. Explain the sequence of system calls a server must make to wait for a connection.
*What do `socket()`, `bind()`, `listen()`, and `accept()` do? What is the analogy for each inside a corporate building?*

---

### 3. What happens to a client program when it calls `connect()` but no server is listening?
*What error does the kernel return? Trace this syscall behavior in your mind.*

---

### 4. How does `INADDR_ANY` (binding to `0.0.0.0`) differ from binding to a specific IP like `127.0.0.1`?
*If a mail clerk binds to `0.0.0.0`, which doors is he watching for mail?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions confidently, you have mastered the Fake Tray. You are ready to step out of the single-machine sandbox and into the Crowded Hallway!
