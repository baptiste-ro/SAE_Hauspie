#include "extractor_U.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint32_t extract_rd_U(uint32_t word) {
    return (word >> 7) & 0x1f;
}

void afficher_binaire(uint32_t valeur) {
    for (int i = 31; i >= 0; i--) {
        printf("%c", (valeur & (1U << i)) ? '1' : '0');
        if (i % 4 == 0) printf(" ");  // Pour regrouper par 4 bits
    }
    printf("\n");
}

uint32_t extract_imm_U(uint32_t word) {
    return word & 0xfffff000;
}

void extractor_U(char *buff, uint32_t word) {
    char buffer[35];
    strcat(buff, "x");
    sprintf(buffer, "%u", extract_rd_U(word));
    strcat(buff, buffer);
    strcat(buff, ", ");
    sprintf(buffer, "%u", extract_imm_U(word));
    strcat(buff, buffer);
}