#include "extractor_B.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint32_t extract_rs1_B(uint32_t word) {
    return (word >> 15) & 0x1f;
}

uint32_t extract_rs2_B(uint32_t word) {
    return (word >> 20) & 0x1f;
}

int32_t extension_B(int32_t immediate) {
    // Test du bit de signe sur 12 bits
    if ((immediate >> 11) & 1) {
    // Extension à 32 bits en mettant à 1 les 20 bits de poids fort
        return immediate | 0xfffff000;
    }
    return immediate;
}

uint32_t extract_imm_B(uint32_t word) {
    int32_t imm_11 = (word >> 7) & 0x1;
    int32_t imm_1_4 = (word >> 8) & 0xf;
    int32_t imm_5_10 = (word >> 25) & 0x3f;
    int32_t imm_12 = (word >> 31) & 0x1;

    // On recolle les morceaux
    int32_t imm = imm_1_4 << 1 | imm_5_10 << 5 | imm_11 << 11 | imm_12 << 12;

    // On étend le bit de signe
    return extension_B(imm);

}

void extractor_B(char *buff, uint32_t word) {
    char buffer[35];
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rs1_B(word));
    strcat(buff, buffer);
    strcat(buff, ", ");
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rs2_B(word));
    strcat(buff, buffer);
    strcat(buff, ", ");
    sprintf(buffer, "%u", extract_imm_B(word));
    strcat(buff, buffer);
}