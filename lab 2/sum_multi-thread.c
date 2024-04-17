#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Struct to pass argument to thread
struct thread_data
{
    int start;
    int end;
    unsigned long long result;
};

// Function for thread to calc sum for start to end
void *calcSum(void *threadData)
{
    struct thread_data *data;
    data = (struct thread_data*) threadData;
    unsigned long long sum = 0;
    for (int i = data -> start; i <= data -> end; i++)
    {
        sum += i;
    }
    data -> result = sum;
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s numThread n\n", argv[0]);
    }
    int numThread = atoi(argv[1]);
    int n = atoi(argv[2]);
    if (n <= 0 || numThread <= 0)
    {
        printf("n and numThread must be > 0");
        return 1;
    }
    pthread_t threads[numThread];
    struct thread_data threadData[numThread];
    
    // Divine the range for each thread
    int range = n / numThread;
    int rc;
    for (int i = 0; i < numThread; i++)
    {
        threadData[i].start = i * range + 1;
        threadData[i].end = (i == numThread - 1)? n : (i + 1) * range;
        rc = pthread_create(&threads[i], NULL, calcSum, &threadData[i]);
        if (rc)
        {
            printf ("Error creating thread\n");
        }
    }
    unsigned long long sum = 0;
    
    // Wait for all threads finish
    for (int i = 0; i < numThread; i++)
    {
        rc = pthread_join(threads[i], NULL);
        if (rc)
        {
            printf ("Error joining thread\n");
        }
        sum += threadData[i].result;
    }
    printf("Sum from 1 to %d is %llu\n", n, sum);
    return 0;
}
