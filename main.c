#include "stdio.h"
#include "string.h"
#include "zip.h"

#define DICT_LEN 62
#define PIN_LEN 4

int main(int argc, char **args) {
    if (argc != 2) {
        printf("No zipfile given");
        return 1;
    }
    FILE *output = fopen("data/output.txt", "w");
    //not searching for '\0'. Is it linux? is it windows?
    char TARGET[50] = "This is a sample text file for OpenMPI and OpenMP.";
    char DICT[DICT_LEN] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char PIN[PIN_LEN + 1];
    char BUFFER[sizeof(TARGET)];
    memset(PIN, 0, sizeof(PIN));
    memset(BUFFER, 0, sizeof(BUFFER));

    zip_t *archive;
    zip_file_t *zippedFile;
    zip_error_t *zipError;

    archive = zip_open(args[1], ZIP_RDONLY, NULL);
    int unzipStatus = -1;
    for (int i = 0; i < DICT_LEN; i++) {
        PIN[0] = DICT[i];
        for (int j = 0; j < DICT_LEN; j++) {
            PIN[1] = DICT[j];
            for (int k = 0; k < DICT_LEN; k++) {
                PIN[2] = DICT[k];
                for (int l = 0; l < DICT_LEN && unzipStatus != 0; l++) {
                    PIN[3] = DICT[l];
                    printf("\ri=%d/%d", i + 1, DICT_LEN);
                    zippedFile = zip_fopen_encrypted(archive, "test.txt", ZIP_FL_ENC_RAW, PIN);
                    if (zippedFile != NULL) {
                        zip_fread(zippedFile, BUFFER, sizeof(BUFFER));
                        zipError = zip_file_get_error(zippedFile);
                        if (zipError->sys_err == 0 && zipError->zip_err == 0 &&
                            strncmp(BUFFER, TARGET, sizeof(TARGET)) == 0) {
                            unzipStatus = 0;
                            fprintf(output, "PIN:%s\n", PIN);
                            printf("\nFound PIN:%s\n", PIN);
                            fwrite(BUFFER, sizeof(char), sizeof(TARGET), output);
                        }
                        zip_fclose(zippedFile);
                    }
                }
            }
        }
    }
    zip_close(archive);
    fclose(output);
    return 0;
}

