#include <stdio.h>
#include <stdint.h>

int main() {
    FILE *f = fopen("test.bin", "wb");
    if (!f) return 1;

    // Instructions RISC-V codées en hexadécimal
    uint32_t instructions[] = {
        0x06400093, // addi x10, x0, 0
        0x0c800113, // addi x10, x0, 1
        0x010005b7, // addi x10, x0, 2
        0x00400513, // beq x0, x0, 0
        0x01f01013,
        0x00100073,
        0x40705013,
        0x0000006f,
        0x00008067,
    };

    for (int i = 0; i < sizeof(instructions)/sizeof(instructions[0]); i++) {
        fwrite(&instructions[i], sizeof(uint32_t), 1, f);
    }

    fclose(f);
    return 0;
}