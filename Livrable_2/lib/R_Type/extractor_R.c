#include "extractor_R.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint32_t extract_rs1_R(uint32_t word) {
    return (word >> 15) & 0x1f;
}

uint32_t extract_rs2_R(uint32_t word) {
    return (word >> 20) & 0x1f;
}

uint32_t extract_rd_R(uint32_t word) {
    return (word >> 7) & 0x1f;
}

void extractor_R(char *buff, uint32_t word) {
    char buffer[35];
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rd_R(word));
    strcat(buff, ", ");
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rs1_R(word));
    strcat(buff, buffer);
    strcat(buff, ", ");
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rs2_R(word));
    strcat(buff, buffer);
    strcat(buff, buffer);
}