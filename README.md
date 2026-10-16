# Mini Linux htop

A lightweight, colorful, terminal-based Linux process monitor built in **C using ncurses**. Mini Linux htop displays running processes alongside system CPU and memory usage, with interactive keyboard shortcuts for sorting and navigation.

## Features

- **Colorful ASCII banner** for a distinctive terminal interface.
- **Live system monitoring** with CPU and memory usage summaries.
- **Process monitoring** displaying PID, username, CPU usage, memory usage, and command.
- **Color-coded interface** with cyan process rows, yellow table headers, and colored CPU usage highlights.
- **Interactive sorting** by CPU usage, memory usage, or PID.
- **Keyboard shortcuts** displayed directly in the interface for easy use.
- **Automatic refresh** every second to keep system and process information updated.

## Preview

Mini Linux htop displays the banner, system summary, keyboard controls, and process table together in one terminal screen.

## Tech Stack

- **Language:** C
- **Terminal UI:** ncurses
- **System information:** Linux `/proc` filesystem
- **Development environment:** Linux / Ubuntu / WSL2
- **Compiler:** GCC

## Requirements

- A Linux environment, including Ubuntu on WSL2.
- GCC compiler.
- ncurses development library.

## Installation and Usage

### 1. Install dependencies

On Ubuntu or WSL2 Ubuntu, run:

```bash
sudo apt update
sudo apt install build-essential libncurses-dev git
```

### 2. Clone the repository

```bash
git clone https://github.com/lingeshg18/Mini-linux-htop.git
cd Mini-linux-htop
```

### 3. Compile the program

```bash
gcc -Wall -Wextra minihtop.c -o minihtop -lncurses
```

### 4. Run the monitor

```bash
./minihtop
```

## Keyboard Shortcuts

| Key | Action |
|---|---|
| `q` | Quit the application |
| `c` | Sort processes by CPU usage, highest first |
| `m` | Sort processes by memory usage, highest first |
| `p` | Sort processes by PID, lowest first |

The available shortcuts are also displayed in the terminal interface.

## How It Works

Mini Linux htop reads system and process information from Linux's `/proc` filesystem.

- **System CPU usage:** Calculated from CPU counters in `/proc/stat` across successive readings.
- **System memory usage:** Calculated using memory information from `/proc/meminfo`.
- **Process information:** Collected from process-specific entries such as `/proc/[pid]/stat`, `/proc/[pid]/status`, `/proc/[pid]/statm`, and `/proc/[pid]/cmdline`.
- **Terminal interface:** ncurses handles screen rendering, colors, keyboard input, and periodic updates.
- **Sorting:** The C standard library's `qsort()` function orders processes according to the selected sorting mode.

## Project Structure

```text
Mini-linux-htop/
├── minihtop.c    # Main application and process monitoring
└── README.md     # Project documentation
```

The exact source-file structure may vary depending on the current repository version.

## Platform Compatibility

The application is designed for Linux environments that expose the `/proc` filesystem and support ncurses.

It can be compiled and run on Ubuntu and Ubuntu under WSL2. It is not a native Windows application.

System resource readings in WSL2 reflect the Linux environment visible to WSL and may differ from Windows Task Manager.

## Future Improvements

- Process filtering and searching.
- Improved handling of terminal resizing and narrow screens.
- More robust process sorting and display.
- Additional system statistics and monitoring features.

## Author

**Lingesh Kumar G**

GitHub: [@lingeshg18](https://github.com/lingeshg18)

---

If you find this project useful, consider giving the repository a star!

