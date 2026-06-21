# Checkpoint: Module 01 · The Tray

> **Feynman Self-Assessment Checklist**
> Ask yourself these questions and see if you can explain them in simple terms (no jargon) to a colleague.

---

### 1. Explain the difference between writing to a normal file on disk and writing to a named pipe (FIFO).
*If a colleague says: "They both look like files in `/tmp`, so they must be the same thing," how do you prove them wrong? What is actually happening in the RAM vs. the storage drive?*

---

### 2. Why does the `open()` call block when you open a named pipe for writing?
*Describe the kernel's role as a matchmaker. What is it waiting for before it lets your write program proceed?*

---

### 3. What does the output of `ls -l` show for a named pipe that differentiates it from a normal file?
*Specifically, what is that first character in the permission string, and what does it tell the OS?*

---

### 4. What system calls are executed when two programs talk via a pipe?
*If you ran `strace` on both programs, which system calls would you see block, and which ones would wake them up?*

---

### Checkpoint Rule:
If you can explain at least **3 out of 4** of these questions without looking at the README, you have mastered this module. If not, go back and run the **Break It** exercise again!
