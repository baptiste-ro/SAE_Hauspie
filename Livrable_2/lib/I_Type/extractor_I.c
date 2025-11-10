#include "extractor_I.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint32_t extract_rd_I(uint32_t word) {
    return (word >> 7) & 0x1f;
}

uint32_t extract_rs1_I(uint32_t word) {
    return (word >> 15) & 0x1f;
}

uint32_t extract_imm_I(uint32_t word) {
    return (word >> 20) & 0xfff;
}

void extractor_I(char *buff, uint32_t word) {
    char buffer[35];
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rd_I(word));
    strcat(buff, buffer);
    strcat(buff, ", ");
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rs1_I(word));
    strcat(buff, buffer);
    strcat(buff, ", ");
    sprintf(buffer, "%u", extract_imm_I(word));
    strcat(buff, buffer);
}