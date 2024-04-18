#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_PATH "shared_file.txt"
#define FILE_SIZE 4096 // 4KB file size

int main() {
    int fd;
    char *mapped_mem;
    const char *message = "Hello from Process 1";

    // Open or create a file
    fd = open(FILE_PATH, O_CREAT | O_RDWR, (mode_t)0600);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // Stretch the file size to the size of the (mmapped) array of ints
    if (lseek(fd, FILE_SIZE-1, SEEK_SET) == -1) {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }

    // Write a single character at the end, ensuring the file actually grows
    if (write(fd, "", 1) == -1) {
        close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }

    // Map the file into memory
    mapped_mem = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED) {
        close(fd);
        perror("Error mapping the file into memory");
        exit(EXIT_FAILURE);
    }

    // Copy message to mapped memory
    strcpy(mapped_mem, message);

    // Close the file descriptor, the mapping still persists
    close(fd);

    printf("Process 1: Wrote message to shared memory.\n");

    // Fork a new process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        printf("Process 2: Reading from shared memory: %s\n", mapped_mem);
        // Modify data in the shared memory
        strcat(mapped_mem, " and Process 2");
        printf("Process 2: Modified shared memory: %s\n", mapped_mem);
    } else { // Parent process
        // Wait for the child to finish
        wait(NULL);
    }

    // Unmap the shared memory
    if (munmap(mapped_mem, FILE_SIZE) == -1) {
        perror("Error unmapping the file from memory");
        exit(EXIT_FAILURE);
    }

    return 0;
}
