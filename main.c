#include "stdio.h"
#include "string.h"
#include "zip.h"
#include <mpi/mpi.h>

#define DICT_LEN 62

int main(int argc, char **args) {
    int unzipStatus = -1;
    if (argc != 2) {
        printf("No zipfile given");
        return 0;
    }
    char PIN[5];
    memset(PIN, 0, sizeof(PIN));
    char DICT[DICT_LEN] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char TARGET[50] = "This is a sample text file for OpenMPI and OpenMP.";

    MPI_Init(&argc, &args);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    zip_t *archive = zip_open(args[1], ZIP_RDONLY, NULL);
    if (archive == NULL) {
        printf("ERank[%d] can't open zip\n", world_rank);
        return 0;
    }
    char BUFFER[sizeof(TARGET)];
    memset(BUFFER, 0, sizeof(BUFFER));

    zip_error_t *zipError;
    zip_file_t *zippedFile;
    for (int i = world_rank * (DICT_LEN / world_size);
         i < (world_rank + 1) * (DICT_LEN / world_size) && unzipStatus != 0; i++) {
        PIN[0] = DICT[i];
        for (int j = 0; j < DICT_LEN && unzipStatus != 0; j++) {
            PIN[1] = DICT[j];
            for (int k = 0; k < DICT_LEN && unzipStatus != 0; k++) {
                PIN[2] = DICT[k];
                for (int l = 0; l < DICT_LEN && unzipStatus != 0; l++) {
                    PIN[3] = DICT[l];
                    zippedFile = zip_fopen_encrypted(archive, "test.txt", ZIP_FL_ENC_RAW, PIN);
                    if (zippedFile != NULL) {
                        zip_fread(zippedFile, BUFFER, sizeof(TARGET));
                        zipError = zip_file_get_error(zippedFile);
                        if (zipError->sys_err == 0 && zipError->zip_err == 0 &&
                            strncmp(BUFFER, TARGET, sizeof(TARGET)) == 0) {
                            unzipStatus = 0;
                            printf("Rank[%d] out of world_size[%d] found message[%s] with pin[%s]\n", world_rank,
                                   world_size,
                                   BUFFER, PIN);
                            MPI_Abort(MPI_COMM_WORLD, 0);
                        }
                        zip_fclose(zippedFile);
                    }
                }
            }
        }
    }
    printf("Rank[%d] out of world_size[%d] found nothing...\n", world_rank, world_size);
    MPI_Finalize();
    zip_close(archive);
    return 0;
}