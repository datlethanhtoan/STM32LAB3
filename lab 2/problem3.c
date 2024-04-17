#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static int pipefd1[2], pipefd2[2];

void INIT(void)
{
    if(pipe(pipefd1) < 0 || pipe(pipefd2) < 0)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}
void WRITE_TO_PARENT(void)
{
    //TODO
    char writeMessage[] = "Hi! This is message from child";
    write(pipefd1[1], writeMessage, sizeof(writeMessage));
    printf("Child send message to parent!\n");
}
void READ_FROM_PARENT(void)
{
    //TODO
    char readMessage[100];
    read(pipefd2[0], readMessage, sizeof(readMessage));
    printf("Child receive message from parent!\n");
    printf("This message is %s\n", readMessage);
    printf("\n");
}
void WRITE_TO_CHILD(void)
{
    //TODO
    char writeMessage[] = "Hello! This is message from parent";
    write(pipefd2[1], writeMessage, sizeof(writeMessage));
    printf("Parent send message to child!\n");
}
void READ_FROM_CHILD(void)
{
    //TODO
    char readMessage[100];
    read(pipefd1[0], readMessage, sizeof(readMessage));
    printf("Parent receive message from child!\n");
    printf("This message is %s\n", readMessage);
    printf("\n");
}
int main(int argc, char* argv[])
{
    INIT();
    pid_t pid;
    pid = fork();
    //set a timer
    alarm(10);
    if (pid == 0)
    {
        while(1)
        {
            sleep(rand() % 2 + 1);
            WRITE_TO_CHILD();
            READ_FROM_CHILD();
        }
    }
    else
    {
        while(1)
        {
            sleep(rand() % 2 + 1);
            READ_FROM_PARENT();
            WRITE_TO_PARENT();
        }
    }
    return 0;
}
