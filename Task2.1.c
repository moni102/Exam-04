#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    fflush(stdout);
    unsigned int totalSum = 0;
    pid_t pid = fork();
    if (-1 == pid)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    
    if (0 == pid)
    {
        for (int i = 0; i < argc; i++)
        {
            pid_t pid = fork();
            if (-1 == pid)
            {
                perror("fork");
                return EXIT_FAILURE;
            }

            if (0 == pid)
            {
                FILE *fr = fopen(argv[i], "r");
                if (NULL == fr)
                {
                    fprintf(stderr, "Reading problem!\n");
                    return EXIT_FAILURE;
                }

                unsigned int currentFileSum = 0;
                fscanf(argv[i], "%lu", currentFileSum);
                totalSum += currentFileSum;
                printf("File %d - %lu\n", i, currentFileSum);
                fclose(fr);
            }
            sleep(1);
        }
    }
    else
    {
        printf("Total sum - %lu\n", totalSum);
    }
    return EXIT_SUCCESS;
}