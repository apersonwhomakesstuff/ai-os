#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((uint16_t*)0xB8000)

static size_t cursor_row = 0;
static size_t cursor_col = 0;
static uint8_t color = 0x0F;

static inline uint16_t vga_entry(unsigned char c, uint8_t fg_bg) {
    return (uint16_t)c | (uint16_t)fg_bg << 8;
}

static void clear_screen(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(' ', color);
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}

static void scroll_if_needed(void) {
    if (cursor_row < VGA_HEIGHT) {
        return;
    }

    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            VGA_MEMORY[(y - 1) * VGA_WIDTH + x] = VGA_MEMORY[y * VGA_WIDTH + x];
        }
    }

    for (size_t x = 0; x < VGA_WIDTH; x++) {
        VGA_MEMORY[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', color);
    }

    cursor_row = VGA_HEIGHT - 1;
}

static void put_char(char c) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
        scroll_if_needed();
        return;
    }

    VGA_MEMORY[cursor_row * VGA_WIDTH + cursor_col] = vga_entry((unsigned char)c, color);
    cursor_col++;

    if (cursor_col >= VGA_WIDTH) {
        cursor_col = 0;
        cursor_row++;
    }

    scroll_if_needed();
}

static void puts(const char* str) {
    while (*str) {
        put_char(*str++);
    }
}

static void print_hex(uint32_t value) {
    const char* hex = "0123456789ABCDEF";
    puts("0x");
    for (int i = 7; i >= 0; i--) {
        uint8_t nibble = (value >> (i * 4)) & 0xF;
        put_char(hex[nibble]);
    }
}

void kmain(uint32_t multiboot_magic, uint32_t multiboot_info) {
    clear_screen();
    puts("AI-OS kernel booted successfully.\n");
    puts("Multiboot magic: ");
    print_hex(multiboot_magic);
    puts("\nMultiboot info: ");
    print_hex(multiboot_info);
    puts("\n\nThis is a freestanding 32-bit C kernel.\n");
    puts("Type support is not implemented yet (no keyboard driver).\n");

    while (1) {
        __asm__ volatile ("hlt");
    }
}
