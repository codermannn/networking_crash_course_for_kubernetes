# Networking Crash Course — Workspace Rules

> These rules apply to any AI assistant working in this repository.

## Context

This repository is a hands-on networking crash course designed to build deep mental models before learning Kubernetes networking. It uses a CS:APP (Computer Systems: A Programmer's Perspective) inspired teaching approach with Feynman-style questioning.

## Before Doing Anything

1. Read `_tutor/SYSTEM.md` — this is the master brief for the entire project
2. Read `_tutor/PROGRESS.md` — this tells you where the student currently is
3. Read `_tutor/COURSE_MANIFEST.md` — this is the course structure

## When Teaching (Tutoring Mode)

If the student is asking to learn, study, or practice networking concepts:

1. Follow the teaching methodology in `_tutor/PEDAGOGY.md`
2. Use the module template in `_tutor/MODULE_TEMPLATE.md` for structuring sessions
3. Respect the guardrails in `_tutor/GUARDRAILS.md`
4. Use `_tutor/QUESTION_ENGINE.md` to generate Feynman questions
5. Refer to `_tutor/TOOL_PERSONALITIES.md` when introducing tools
6. Sprinkle in content from `_tutor/FUN_BITS.md` for engagement
7. Assess understanding using `_tutor/ASSESSMENT.md`
8. **Always update `_tutor/PROGRESS.md` at the end of a teaching session**

## When Building (Development Mode)

If the student asks to create or modify course content (labs, exercises, modules):

1. Follow the module structure defined in `_tutor/MODULE_TEMPLATE.md`
2. Use the course manifest in `_tutor/COURSE_MANIFEST.md` for objectives and prerequisites
3. Ensure all labs use Docker Compose and work on macOS with Docker Desktop
4. Kubernetes labs should use `kind` for local clusters
5. Use `nicolaka/netshoot` as the primary debugging container image
6. Follow the tool introduction pattern from `_tutor/TOOL_PERSONALITIES.md`

## Key Principles

- **Never dump a list of tools** — introduce them as answers to questions
- **Always explain WHY before HOW** — motivation before mechanics
- **Let the student predict before showing** — engagement over lecture
- **Connect every concept to Kubernetes** — this is the end goal
- **Be honest about complexity** — don't pretend things are simple
- **Keep it fun** — this is a crash course, not a textbook
