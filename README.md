# Linux System Monitor 🖥️

A lightweight **Linux System Monitor** written in **C++** that provides real-time system statistics directly in the terminal.  
It tracks **CPU usage**, **memory usage**, and the **top 5 CPU-consuming processes** by reading from the Linux `/proc` filesystem.

This project demonstrates core **Operating Systems concepts** and **system-level programming** in C++.

---

## 🚀 Features

- Real-time global CPU usage
- Memory usage statistics
- Top **5** CPU-consuming processes
- Concurrency-safe CPU calculations
- Modular and efficient C++ design
- No external libraries required

---

## 🛠️ Build & Run

### Prerequisites
- Linux OS
- `g++` (C++17 or later)
- `make`

### Build
```bash
make
```

### Run
```bash
./monitor
```

### Clean
```bash
make clean
```

---

## 📈 Sample Output

```text
=====================================
      JASH LINUX SYSTEM MONITOR     
=====================================
CPU Usage:    14.27 %
Memory Usage: 32.91 %
-------------------------------------
TOP PROCESSES (Active):
1. PID 1321   CPU 6.48 %
2. PID 4512   CPU 4.92 %
3. PID 982   CPU 2.31 %
4. PID 2201   CPU 1.87 %
5. PID 776   CPU 1.12 %
=====================================
```

---

## 🧠 Implementation Overview

- **CPU Monitoring**
  - Reads `/proc/stat`
  - Uses delta-based calculations for accuracy
  - Ensures synchronized timing across measurements

- **Memory Monitoring**
  - Reads `/proc/meminfo`
  - Computes used vs total memory

- **Process Monitoring**
  - Parses `/proc/[pid]/stat`
  - Sorts processes by CPU usage
  - Displays top 5 active processes only

---

## 🎯 Learning Outcomes

- Linux `/proc` filesystem internals
- CPU time accounting
- Process-level resource monitoring
- Safe time-based measurements
- Modular system programming in C++

---

> Simple tools reveal the deepest system concepts.
