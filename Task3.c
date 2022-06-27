#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void *routine(int argc, char **argv, int M)
{
    sleep(1);
    int arr[M];
    FILE *fw = fopen("file1.txt", "a");
    if (NULL == fw)
    {
        fprintf(stderr, "Writing problem!\n");
        return EXIT_FAILURE;
    }
    fprintf("%s %d ", argv[0], argv[1]);
    for (int i = 0; i < M; i++)
    {
        arr[i] = argv[i + 2];
    }
    qsort(arr, M, sizeof(int), cmpfunc);
    for (int i = 0; i < M; i++)
    {
        fprintf("%d ", arr[i]);
    }
    fputc('\n',"file1.txt");
    fclose(fw);
}

int main(int argc, char **argv)
{
    fflush(stdout);
    unsigned int N, M;
    scanf("%lu %lu", N, M);
    pthread_t th[N];
    int arr[M];
    for (int i = 0; i < N; i++)
    {
        if (pthread_create(&th[i], NULL, routine(argc, **argv, M), NULL))
        {
            perror("create");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < N; i++)
        {
            if (pthread_join(th[i], NULL))
            {
                perror("join");
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}