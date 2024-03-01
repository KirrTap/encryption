#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vypocet_kluca(char *kluc);
void sifrovanie(char *input_file, char *output_file, int hodnota_kluca);
void desifrovanie(char *input_file, char *output_file, int hodnota_kluca);

int main(int argc, char *argv[]) {
    if (argc != 8) {
        printf("chyba");
        return 1;
    }

    char *kluc = NULL;
    char *input_file = NULL;
    char *output_file = NULL;
    char *prepinac = NULL;
    int s_d = 0;

    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "-d") == 0) {
            prepinac = argv[i];
            s_d = 1;
        }
        if (strcmp(argv[i], "-p") == 0) {
            kluc = argv[i + 1];
        }
        if (strcmp(argv[i], "-i") == 0) {
            input_file = argv[i + 1];
        }
        if (strcmp(argv[i], "-o") == 0) {
            output_file = argv[i + 1];
        }
    }   

    if (!s_d || prepinac == NULL || kluc == NULL || input_file == NULL || output_file == NULL) {
        printf("chyba");
        return 1;
    }

    int hodnota_kluca = vypocet_kluca(kluc);
    // printf("Prepinac: %s\n", prepinac);
    // printf("Kluc: %s\n", kluc);
    // printf("Hodnota kluca: %d\n", hodnota_kluca);
    // printf("Input file: %s\n", input_file);
    // printf("Output file: %s\n", output_file);

    if (strcmp(prepinac, "-s") == 0) {
        sifrovanie(input_file, output_file, hodnota_kluca);
    } else if (strcmp(prepinac, "-d") == 0) {
        desifrovanie(input_file, output_file, hodnota_kluca);
    }

    return 0;
}

int vypocet_kluca(char *kluc) {
    int ascii_hodnota = 0;
    for (int i = 0; kluc[i] != '\0'; i++) {
        ascii_hodnota += (int) kluc[i]; 
    }

    int hodnota_kluca = ascii_hodnota % 128;
    return hodnota_kluca;
}

void sifrovanie(char *input_file, char *output_file, int hodnota_kluca) {
    FILE *input = fopen(input_file, "r, ccs=UTF-8");
    FILE *output = fopen(output_file, "w, ccs=UTF-8");

    if (input == NULL) {
        printf("chyba");
        return;
    }

    int c;
    while ((c = fgetc(input)) != EOF) {
        c = c + hodnota_kluca;
        if (c > 126) {
            c = c - 94;
        }
        fputc(c, output);
    }

    fclose(input);
    fclose(output);
}

void desifrovanie (char *input_file, char *output_file, int hodnota_kluca) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (input == NULL) {
        printf("chyba");
        return;
    }

    int c;
    while ((c = fgetc(input)) != EOF) {
        c = c - hodnota_kluca;
        if (c < 32) {
            c = c + 94;
        }
        fputc(c, output);
    }

    fclose(input);
    fclose(output);
}
