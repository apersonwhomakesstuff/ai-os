# AI-OS

A small, freestanding 32-bit operating system kernel written mostly in C with a tiny NASM bootstrap.

## Build

```bash
make
```

## How to add/install GRUB tools

You need the `grub-mkrescue` utility (and ISO backend tools like `xorriso`) to create a **bootable** ISO.

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install -y grub-pc-bin xorriso mtools
```

### Fedora

```bash
sudo dnf install -y grub2-tools xorriso mtools
```

### Arch Linux

```bash
sudo pacman -S grub xorriso mtools
```

### macOS (Homebrew)

```bash
brew install xorriso mtools
# GRUB itself is usually built in a Linux environment/VM/container for multiboot ISO workflows.
```

### Windows (recommended: WSL2)

GRUB ISO tooling is Linux-first, so the easiest Windows path is **WSL2** (Ubuntu).

1. Install WSL2 + Ubuntu (PowerShell as Administrator):

```powershell
wsl --install -d Ubuntu
```

2. Open Ubuntu (WSL shell), then install tools:

```bash
sudo apt update
sudo apt install -y build-essential nasm grub-pc-bin xorriso mtools
```

3. Build from the project folder inside WSL:

```bash
make iso
```

If you do not want WSL, use a Linux VM (VirtualBox/VMware) and run the same Linux commands there.

Verify installation:

```bash
grub-mkrescue --version
```

## FAQ

### “Can I just drop in one `grub.c` file?”

Short answer: **no**.

GRUB is a separate bootloader project, not a single C source file you embed into your kernel. In this repo, GRUB is used externally to load your multiboot kernel using:

- `grub/grub.cfg` (boot menu/config)
- `grub-mkrescue` (builds a bootable ISO image)

So the normal workflow is: keep your kernel code in C/ASM, and let GRUB boot it.

## Build ISO artifact

```bash
make iso
```

If `grub-mkrescue` is available, this produces a bootable ISO at `build/ai-os.iso`.
If not available in the environment, the script creates a fallback `.iso` artifact containing the boot tree for portability.
