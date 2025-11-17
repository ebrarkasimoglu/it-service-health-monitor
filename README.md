# IT Service Health Monitor (C++)

This is a small C++ project that simulates the health of several IT services (e.g. database, auth, network) and calculates a simple overall risk level based on their status.

The goal is to practice object-oriented thinking in C++ (struct, enum, vectors) and to connect it with a basic operational risk perspective.

---

## What it does

- defines a set of critical IT services (DATABASE, AUTH, NETWORK, BACKUP, LOGGING)
- assigns each service a random health status:
  - `OK`
  - `WARN`
  - `CRITICAL`
- maps each status to a numerical risk score
- sums up all risk scores and classifies the overall level as:
  - `LOW`
  - `MEDIUM`
  - `HIGH`
- prints a short summary to the console
- appends a snapshot of the current state to a log file (`logs/system_log.txt`)

---

## Project structure

```text
it-service-health-monitor/
 ├── src/
 │   └── it_risk_monitor.cpp   # main C++ source file
 ├── logs/                     # log directory (created manually)
 │   └── system_log.txt        # created/extended at runtime
 └── README.md
