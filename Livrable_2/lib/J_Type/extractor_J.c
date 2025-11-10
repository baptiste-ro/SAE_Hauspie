#include "extractor_J.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint32_t extract_rd_J(uint32_t word) {
    return (word >> 7) & 0x1f;
}

int32_t extension_J(int32_t immediate) {
    // Test du bit de signe sur 12 bits
    if ((immediate >> 19) & 1) {
    // Extension à 32 bits en mettant à 1 les 20 bits de poids fort
        return immediate | 0xfffff000;
    }
    return immediate;
}

uint32_t extract_imm_J(uint32_t word) {
    int32_t imm_12_19 = (word >> 12) & 0xff;
    int32_t imm_11 = (word >> 20) & 0x1;
    int32_t imm_1_10 = (word >> 21) & 0x3f;
    int32_t imm_20 = (word >> 31) & 0x1;

    // On recolle les morceaux
    int32_t imm = imm_1_10 << 1 | imm_11 << 11 | imm_12_19 << 12 | imm_20 << 20;

    // On étend le bit de signe
    return extension_J(imm);

}

void extractor_J(char *buff, uint32_t word) {
    char buffer[35];
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rd_J(word));
    strcat(buff, buffer);
    strcat(buff, ", ");
    sprintf(buffer, "%u", extract_imm_J(word));
    strcat(buff, buffer);
}