#include "extractor_S.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint32_t extract_rs1_S(uint32_t word) {
    return (word >> 15) & 0x1f;
}

uint32_t extract_rs2_S(uint32_t word) {
    return (word >> 20) & 0x1f;
}

int32_t extension_S(int32_t immediate) {
    // Test du bit de signe sur 12 bits
    if ((immediate >> 11) & 1) {
    // Extension à 32 bits en mettant à 1 les 20 bits de poids fort
        return immediate | 0xfffff000;
    }
    return immediate;
}

uint32_t extract_imm_S(uint32_t word) {
    int32_t imm_0_4 = (word >> 7) & 0x1f;
    int32_t imm_5_11 = (word >> 25) & 0x7f;

    // On recolle les morceaux
    int32_t imm = imm_0_4 | imm_5_11 << 5;

    // On étend le bit de signe
    return imm;

}

void extractor_S(char *buff, uint32_t word) {
    char buffer[35];
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rs1_S(word));
    strcat(buff, buffer);
    strcat(buff, ", ");
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rs2_S(word));
    strcat(buff, buffer);
    strcat(buff, ", ");
    sprintf(buffer, "%u", extract_imm_S(word));
    strcat(buff, buffer);
}