# AI-OS

A small, freestanding 32-bit operating system kernel written mostly in C with a tiny NASM bootstrap.

## Build

```bash
make
```

## Build ISO artifact

```bash
make iso
```

If `grub-mkrescue` is available, this produces a bootable ISO at `build/ai-os.iso`.
If not available in the environment, the script creates a fallback `.iso` artifact containing the boot tree for portability.
