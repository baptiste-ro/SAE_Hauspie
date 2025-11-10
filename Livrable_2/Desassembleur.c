#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lib/B_Type/extractor_B.h"
#include "lib/I_Type/extractor_I.h"
#include "lib/J_Type/extractor_J.h"
#include "lib/R_Type/extractor_R.h"
#include "lib/S_Type/extractor_S.h"
#include "lib/U_Type/extractor_U.h"

int32_t extractor_opcode(uint32_t word) {
    return word & 0x7f;
}

int8_t extractor_funct3(uint32_t word) {
   return (word >> 12) & 0x7;
}

int32_t extractor_funct7(uint32_t word) {
    return (word >> 25) & 0x7f;
}

int32_t extractor_I_funct12(uint32_t word) {
    return (word >> 20) & 0xfff;
}

void lecture_32_bits(FILE *file, int profondeur) {
    if (feof(file)) {
        return;
    }
    
    uint32_t word;

    if (fread(&word, 4, 1, file)) {
        int8_t opcode = extractor_opcode(word);
        char line[255];
        int8_t funct3 = 0;
        int8_t funct7 = 0;

        switch (opcode) {
        case 0b1100011:         // BRANCH
            funct3 = extractor_funct3(word);
            switch(funct3) {
                case 0b000:
                    strcpy(line, "BEQ               ");
                    break;
                case 0b001:
                    strcpy(line, "BNE               ");
                    break;
                case 0b100:
                    strcpy(line, "BLT               ");
                    break;
                case 0b101:
                    strcpy(line, "BGE               ");
                    break;
                case 0b110:
                    strcpy(line, "BLTU              ");
                    break;
                case 0b111:
                    strcpy(line, "BGEU              ");
                    break;
            }

            extractor_B(line, word);

            break;
        case 0b0000011:         // LOAD
            funct3 = extractor_funct3(word);
            switch(funct3) {
                case 0b000:
                    strcpy(line, "LB                ");
                    break;
                case 0b001:
                    strcpy(line, "LH                ");
                    break;
                case 0b010:
                    strcpy(line, "LW                ");
                    break;
                case 0b100:
                    strcpy(line, "LBU               ");
                    break;
                case 0b101:
                    strcpy(line, "LHU              ");
                    break;
            }

            extractor_I(line, word);

            break;
        case 0b1100111:         // JALR
            strcpy(line, "JALR              ");
            extractor_I(line, word);

            break;
        case 0b0001111:         // MISC-MEM
            strcpy(line, "FENCE             ");
            extractor_I(line, word);

            break;
        case 0b0010011:         // OP-IMM
            funct3 = extractor_funct3(word);
            switch(funct3) {
                case 0b000:
                    strcpy(line, "ADDI              ");
                    break;
                case 0b010:
                    strcpy(line, "SLTI              ");
                    break;
                case 0b011:
                    strcpy(line, "SLTIU             ");
                    break;
                case 0b100:
                    strcpy(line, "XORI              ");
                    break;
                case 0b110:
                    strcpy(line, "ORI               ");
                    break;
                case 0b111:
                    strcpy(line, "ANDI              ");
                    break;
                case 0b001:
                    strcpy(line, "SLLI              ");
                    break;
                case 0b101:
                    funct7 = extractor_funct7(word);
                    switch(funct7) {
                        case 0b0000000:
                            strcpy(line, "SRLI              ");
                            break;
                        case 0b0100000:
                            strcpy(line, "SRAI              ");
                    }
                    break;
            }
            extractor_I(line, word);
            break;
        case 0b1110011:         // SYSTEM
            
            int8_t I_funct12 = extractor_I_funct12(word);
            switch(I_funct12) {
                case 0b000000000000:
                    strcpy(line, "ECALL             ");
                    break;
                case 0b000000000001:
                    strcpy(line, "EBREAK            ");
                    break;
            }

            break;
        case 0b1101111:         // JAL
            
            strcpy(line, "JAL               ");
            extractor_J(line, word);

            break;
        case 0b0110011:         // OP
            
            funct3 = extractor_funct3(word);
            switch(funct3) {
                case 0b000:
                    funct7 = extractor_funct7(word);
                    switch(funct7) {
                        case 0b0000000:
                            strcpy(line, "ADD               ");
                            break;
                        case 0b0100000:
                            strcpy(line, "SUB               ");
                    }
                    break;
                case 0b001:
                    strcpy(line, "SLL               ");
                    break;
                case 0b010:
                    strcpy(line, "SLT               ");
                    break;
                case 0b011:
                    strcpy(line, "SLTU              ");
                    break;
                case 0b100:
                    strcpy(line, "XOR               ");
                    break;
                case 0b101:
                    funct7 = extractor_funct7(word);
                    switch(funct7) {
                        case 0b0000000:
                            strcpy(line, "SRL               ");
                            break;
                        case 0b0100000:
                            strcpy(line, "SRA               ");
                    }
                    break;
                case 0b110:
                    strcpy(line, "OR                ");
                    break;
                case 0b111:
                    strcpy(line, "AND               ");
                    break;
            }
            extractor_R(line, word);
            break;
        case 0b0100011:         // STORE
            funct3 = extractor_funct3(word);
            switch(funct3) {
                case 0b000:
                    strcpy(line, "SB                ");
                    break;
                case 0b001:
                    strcpy(line, "SH                ");
                    break;
                case 0b010:
                    strcpy(line, "SW                ");
                    break;
            }
            extractor_S(line, word);
            break;
        case 0b0010111:         // AUPIC
            strcpy(line, "AUPIC             ");
            extractor_U(line, word);
            break;
        case 0b0110111:         // LUI
            strcpy(line, "LUI               ");
            extractor_U(line, word);
            break;
        default:
            strcpy(line, "UNKNOWN           ");
            break;
        }

        printf("%08x: %s\n", profondeur, line);
        lecture_32_bits(file, profondeur + 4);
    }
}

void lecture_file(const char *path) {
    FILE *file = fopen(path, "rb");

    if(!file) {
        perror("File is invalid or doesn't exist.");
        return;
    }

    lecture_32_bits(file, 0);
    fclose(file);
}

char* error_message() {
    return "Un désassembleur RISC-V pour le jeu d'instruction RV32I\n\nUtilisation: disas [OPTIONS] FICHIER_BIN\n\nArguments:\n    FICHIER_BIN             Un fichier contenant les instructions à désassembler\n\nOptions:\n    -h                      Affiche ce message d'aide\n\n";
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./decodeur <fichier_binaire>\n");
        return 1;
    } else if (strcmp(argv[1], "-h") == 0) {
        printf("%s", error_message());
    } else {
        lecture_file(argv[1]);
    }
    
    return 0;
}