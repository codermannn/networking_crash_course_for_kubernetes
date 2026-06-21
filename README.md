# The Networking Crash Course

> *"I learned very early the difference between knowing the name of something and knowing something."* — Richard Feynman

Welcome. This is not a textbook. This is an investigation.

Every networking concept that exists is simply an invention designed to fix the limitation of the concept that came before it. You cannot understand the invention until you physically feel the pain of the limitation.

You will not be lectured. You will be given broken situations, tools to investigate them, and the freedom to break things further. The understanding will come from your own hands.

## How This Works

Every module follows the same 8-step **Discovery Loop**:

1. 🔥 **The Burn** — Something doesn't work. You see the failure.
2. 🤔 **Your Prediction** — Before touching anything: *what do you think is happening?*
3. 🔬 **The Experiment** — Run the command. See the raw truth.
4. 😮 **The Gap** — Your prediction was wrong. *Why?*
5. 🧠 **The Mechanism** — Now we explain. Simple words first. Jargon last.
6. 🔍 **The Verification** — Prove it by reading the kernel's own memory.
7. 💥 **Break It** — Destroy the mechanism on purpose. Watch the predictable failure.
8. ➡️ **The Next Burn** — The limitation of what we just learned creates the next problem.

Read [PEDAGOGY.md](PEDAGOGY.md) for the complete teaching philosophy.

## Prerequisites

- **Docker Desktop** installed on macOS
- **Two terminal windows** (you'll need them constantly)
- **Curiosity** (required)
- **Fear of breaking things** (leave it at the door)

## Your Journey

### Act I: Two Programs Talking
> *How do two programs share data when the OS walls off their memory?*

- [ ] **[01 · The Tray](act-1--two-programs-talking/01-the-tray/)** — How do they pass a note on the same computer?
- [ ] **[02 · The Fake Tray](act-1--two-programs-talking/02-the-fake-tray/)** — What if they're in different buildings?

### Act II: The Crowded Hallway
> *If 10 computers share a wire, how does the mail slot know which letter is for you?*

- [ ] **[03 · The Serial Number](act-2--the-crowded-hallway/03-the-serial-number/)** — How do we ignore the noise?
- [ ] **[04 · The Shout](act-2--the-crowded-hallway/04-the-shout/)** — How do we find the hardware serial number?

### Act III: Escaping the Building
> *What happens when one hallway isn't big enough?*

- [ ] **[05 · The Walls](act-3--escaping-the-building/05-the-walls/)** — How do we stop everyone from shouting at once?
- [ ] **[06 · The Room Number](act-3--escaping-the-building/06-the-room-number/)** — If I leave the room, how does mail find me?
- [ ] **[07 · The Map](act-3--escaping-the-building/07-the-map/)** — How does the mail clerk know which direction to send the mail?
- [ ] **[08 · The Gossip](act-3--escaping-the-building/08-the-gossip/)** — How do the mail clerks automatically map the entire world?

### Act IV: The Conversation
> *How do we make sure the letter arrives intact, and to the right person?*

- [ ] **[09 · The Desk Number](act-4--the-conversation/09-the-desk-number/)** — Five people in the room. Who opens the mail?
- [ ] **[10 · The Registered Mail](act-4--the-conversation/10-the-registered-mail/)** — The mailman lost half the pages. How do we fix this?
- [ ] **[11 · The Paper Airplane](act-4--the-conversation/11-the-paper-airplane/)** — What if we don't care about lost pages, we just want speed?

### Act V: Making It Human
> *How do we make this system work for 8 billion non-engineers?*

- [ ] **[12 · The Phonebook](act-5--making-it-human/12-the-phonebook/)** — How do I find my friend without memorizing their address?
- [ ] **[13 · The Con Artist](act-5--making-it-human/13-the-con-artist/)** — We ran out of addresses. How do billions of devices still connect?

---

When you finish this course, you won't just know networking terminology. You will understand the engineering decisions of the people who built the internet. You will be able to diagnose failures by reading the kernel's own handwriting.

**[Begin: Act I, Question 1 → The Tray](act-1--two-programs-talking/01-the-tray/)**
