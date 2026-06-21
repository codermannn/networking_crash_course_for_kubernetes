# Tools: Module 01 · The Tray

## mkfifo
**What it answers:** "How do I create a shared memory buffer (named pipe) that pretends to be a file?"
**How we use it in this module:** To create `/tmp/my_tray` which allows two terminal processes to communicate.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `mkfifo <name>` | Create a named pipe at the specified path |
| `ls -l <name>` | Check details (look for `p` at the start of permissions, meaning "pipe") |

---

## strace
**What it answers:** "What actual requests (system calls) is my program making to the OS kernel?"
**How we use it in this module:** To watch `read()` and `write()` system calls block and unblock each other.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `strace <command>` | Run command and print all system calls to stderr |
| `strace -e openat,read,write <command>` | Filter trace to only show file open, read, and write calls |
| `strace -p <PID>` | Attach to an already running process by its ID |

---

## ls -l
**What it answers:** "What kind of file is this and what are its metadata properties?"
**How we use it in this module:** To identify named pipes and normal files.
**Quick reference:**
| Command | What it does |
|---------|-------------|
| `ls -l <path>` | Long listing showing file type, permissions, links, owner, size, and modification time |
