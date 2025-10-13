#include <stdio.h>
#include <stdint.h>

int32_t extract_opcode(uint32_t word) {
    return word & 0x7f;
}

void lecture_32_bits(FILE *file, int profondeur) {
    if (feof(file)) {
        return;
    }
    
    uint32_t word;

    if (fread(&word, 4, 1, file)) {
        int8_t opcode = extract_opcode(word);
        const char *str_opcode;
        const char *encoding;
        switch (opcode) {
        case 0b1100011:
            str_opcode = "BRANCH";
            encoding = "I";
            break;
        case 0b1100111:
            str_opcode = "JALR";
            encoding = "I";
            break;
        case 0b0000011:
            str_opcode = "LOAD";
            encoding = "I";
            break;
        case 0b0001111:
            str_opcode = "MISC-MEM";
            encoding = "I";
            break;
        case 0b0010011:
            str_opcode = "OP-IMM";
            encoding = "I";
            break;
        case 0b1110011:
            str_opcode = "SYSTEM";
            encoding = "I";
            break;
        case 0b1101111:
            str_opcode = "JAL";
            encoding = "U_J";
            break;
        case 0b0110011:
            str_opcode = "OP";
            encoding = "R";
            break;
        case 0b0100011:
            str_opcode = "STORE";
            encoding = "S";
            break;
        case 0b0010111:
            str_opcode = "AUIPC";
            encoding = "U";
            break;
        case 0b0110111:
            str_opcode = "LUI";
            encoding = "U";
            break;
        default:
            str_opcode = "Unknown";
            encoding = "Unknown";
            break;
        }

        printf("%08x,%08x,%s,%s\n", profondeur, word, str_opcode, encoding);
        lecture_32_bits(file, profondeur + 4);
    }
}

void lecture_file(const char *path) {
    FILE *file = fopen(path, "rb");

    printf("offset,valeur,opcode,encoding\n");

    if(!file) {
        perror("File is invalid or doesn't exist.");
        return;
    }

    lecture_32_bits(file, 0);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./decodeur <fichier_binaire>\n");
        return 1;
    }

    lecture_file(argv[1]);
    return 0;
}