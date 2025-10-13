#include <stdio.h>
#include <stdint.h>

int main() {
    FILE *f = fopen("test.bin", "wb");
    if (!f) return 1;

    // Instructions RISC-V codées en hexadécimal
    uint32_t instructions[] = {
        0x00000513, // addi x10, x0, 0
        0x00100513, // addi x10, x0, 1
        0x00200513, // addi x10, x0, 2
        0x00000063, // beq x0, x0, 0
        0x0000006F  // jal x0, 0
    };

    for (int i = 0; i < 5; i++) {
        fwrite(&instructions[i], sizeof(uint32_t), 1, f);
    }

    fclose(f);
    return 0;
}