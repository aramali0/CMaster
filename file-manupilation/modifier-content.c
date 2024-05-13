#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file = fopen("fileTest.txt", "r+");
    char output[100];
    char temp[100];
    char *position;

    if (file == NULL) {
        printf("Error while opening the file!\n");
    } else {
        fputs("Le noyau réalise une préemption du processeur lorsqu’il dépasse son temps.", file);
        printf("File before modification:\n");
        rewind(file); 
        while (fgets(output, sizeof(output), file) != NULL) {
            printf("%s", output);
        }
        position = strstr(output, "son temps");
        if (position != NULL) {
            int index = position - output;
            fseek(file, index, SEEK_SET);
            fgets(temp, sizeof(temp), file);
            fseek(file, index, SEEK_SET);
            fputs(" quantum de", file);
            fputs(temp, file);
            printf("\nFile after modification:\n");
            rewind(file); 
            while (fgets(output, sizeof(output), file) != NULL) {
                printf("%s", output);
            }
        } else {
            printf("\n\"son temps\" not found in the file.\n");
        }

        fclose(file);
    }

    return 0;
}

