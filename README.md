# Mini Linux htop

A lightweight, terminal-based Linux process monitor written in **C** using the **ncurses** library. The project displays running processes and selected system resource metrics in a colorful, continuously refreshed terminal interface.

## Features

- Displays process IDs (PID) and usernames.
- Shows CPU usage and memory usage percentages for processes.
- Displays process command information.
- Refreshes process information approximately every second.
- Uses ncurses for terminal-based rendering and colors.
- Reads process and system information from the Linux `/proc` filesystem.

## Tech Stack

- **Language:** C
- **Terminal UI:** ncurses
- **Operating System:** Linux
- **System interfaces:** `/proc` filesystem and POSIX system calls

## Preview

<!-- Add a screenshot after saving it to the screenshots/ directory. -->
<!-- ![Mini Linux htop running in a terminal](screenshots/minihtop.png) -->

## Prerequisites

You need:
- A Linux environment
- GCC or another compatible C compiler
- The ncurses development library
- A terminal that supports ncurses

### Install dependencies

**Ubuntu / Debian**
```bash
sudo apt update
sudo apt install build-essential libncurses-dev
```

**Fedora**
```bash
sudo dnf install gcc make ncurses-devel
```

**Arch Linux**
```bash
sudo pacman -S --needed base-devel ncurses
```

## Installation and Usage

Clone the repository:

```bash
git clone https://github.com/lingeshg18/Mini-linux-htop.git
cd Mini-linux-htop
```

Compile the program:

```bash
gcc -Wall -Wextra minihtop.c -o minihtop -lncurses
```

Run it:

```bash
./minihtop
```

Use `Ctrl+C` to stop the program.

## How It Works

1. Reads system CPU statistics from `/proc/stat`.
2. Reads process information from `/proc`, including process status, memory information, and command details.
3. Calculates CPU usage from changes in CPU-time counters.
4. Estimates process memory usage using resident-memory information and total system memory.
5. Renders the process information in the terminal using ncurses and refreshes it periodically.

## Platform Compatibility

This version is designed for **Linux systems** with a compatible `/proc` filesystem and ncurses development libraries.

It is not currently a universal Windows/macOS application. Supporting other operating systems would require platform-specific process-monitoring implementations.

## Limitations

- The current implementation stores information for a maximum of 1,024 processes.
- Process visibility depends on operating-system permissions and process availability.
- CPU and memory readings should be treated as estimates and validated against established monitoring tools.
- Terminal dimensions and character support may affect the display.

## Future Improvements

- Add sorting and filtering by CPU and memory usage.
- Implement keyboard controls and graceful shutdown.
- Improve CPU and memory calculation accuracy.
- Add a Makefile and automated build checks.
- Add screenshots and tested release binaries.

## Author

**Lingesh Kumar G**

- GitHub: [@lingeshg18](https://github.com/lingeshg18)

## License

No license has been specified yet. Add a license file if you intend to define the terms under which others can use, modify, or distribute this project.
