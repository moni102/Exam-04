#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

unsigned int totalSum = 0;
int currentFile = 1;

void *routine(int argc, char **argv)
{
    unsigned int currentFileSum = 0;
    sleep(1);
    FILE *fw = fopen(argv[currentFile++], "wb");
    if (NULL == fw)
    {
        fprintf(stderr, "Reading problem!\n");
        return EXIT_FAILURE;
    }

    unsigned int currentFileSum = 0;
    fscanf(argv[currentFile], "%lu", currentFileSum);
    totalSum += currentFileSum;
    printf("File %d - %lu\n", currentFile, currentFileSum);
    fclose(fw);
}
int main(int argc, char **argv)
{
    fflush(stdout);
    unsigned int totalSum = 0;
    pthread_t th[argc];
    for (int i = 0; i < argc; i++)
    {
        if (pthread_create(&th[i], NULL, routine(argc, **argv), NULL))
        {
            perror("create");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < argc; i++)
        {
            if (pthread_join(th[i], NULL))
            {
                perror("join");
                exit(EXIT_FAILURE);
            }
        }
    }
    return EXIT_SUCCESS;
}