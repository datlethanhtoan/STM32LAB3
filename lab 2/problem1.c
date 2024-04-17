#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
// Structure to store shared data
struct SharedData {
    double rating1[1683];
    double rating2[1683];
};

// Function to calculate rating
double *ratingCalc(const char *filename) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Failed to open file");
        return NULL;
    }

    int userID, movieID, rating;
    unsigned long timeStamp;
    double *ratingArray = (double*)calloc(1683, sizeof(double));
    if (ratingArray == NULL) 
    {
        perror("Failed to allocate memory for ratingArray");
        return NULL; // or handle the error in your own way
    }
    for (int i = 0; i < 1683; i++)
    {
    	ratingArray[i] = 0;
    }
    int count[1683] = {0};

    while (fscanf(file, "%d\t%d\t%d\t%lu", &userID, &movieID, &rating, &timeStamp) == 4) 
    {
        ratingArray[movieID] += rating;
        count[movieID]++;
    }
    fclose(file);
    for (int i = 0; i < 1683; i++)
    {
    	if (count[i] > 0) ratingArray[i] = ratingArray[i] / count[i];
    }
    return ratingArray;
}

int main() {
    key_t key = IPC_PRIVATE; // Key for shared memory
    int shmid;
    struct SharedData* shared_data;

    // Create shared memory
    shmid = shmget(key, sizeof(struct SharedData), 0666 | IPC_CREAT);
    if (shmid < 0) 
    {
        perror("Failed to create shared memory");
        return 1;
    }

    // Attach the shared memory segment
    shared_data = (struct SharedData*)shmat(shmid, 0, 0);
    if (shared_data == (struct SharedData*)-1) 
    {
        perror("Failed to attach shared memory");
        return 1;
    }

    // Spawn two child processes
    for (int i = 0; i < 2; i++)
    {
        pid_t pid = fork();
        if (pid < 0) 
        {
            perror("Failed to fork");
            return 1;
        } 
        else if (pid == 0) 
        {
            // Child process: calculate rating and write to shared memory
            double *rating = ratingCalc(i == 0 ? "movie-100k_1.txt" : "movie-100k_2.txt");
            if (i == 0) 
            {
                memcpy(shared_data -> rating1, rating, 1683 * sizeof(double));
            } 
            else 
            {
                memcpy(shared_data -> rating2, rating, 1683 * sizeof(double));
            }
            free(rating);
            exit(0);
        }
    }

    // Parent process: wait for child processes to finish
    for (int i = 0; i < 2; i++) 
    {
        wait(NULL);
    }

    // Access shared data and print rating
    printf("Rating in movie-100k_1.txt:\n");
    for (int i = 1; i <= 1682; i++)
    {
        printf("movieID: %d\trating: %.2f\n", i, shared_data -> rating1[i]);
    }
    printf("Rating in movie-100k_2.txt:\n");
    for (int i = 1; i <= 1682; i++)
    {
        printf("movieID: %d\trating: %.2f\n", i, shared_data -> rating2[i]);
    }
    // Detach and remove shared memory
    if (shmdt(shared_data) == -1)
    {
        perror("Failed to detach shared memory");
        return 1;
    }
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        perror("shmtcl");
        return 1;
    }
    return 0;
}
