#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;
    const int numberofChildren = 3;

    //Array of commands
    char *commands[][3] = {
        {"ls", "-l",NULL} ,//Command to list directory contents
        {"echo", "Hello from CS470",NULL}, //command 
        {"date", NULL,NULL}, //Command to list directory contents

    };

    printf("Parent process PID: %d\n", getpid());



    for(int i=0; i< numberofChildren; i++) {
        pid = fork();
        if (pid <0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }else if (pid ==0){
            printf("Child process PID: %d - Executing command: %s\n", getpid(), commands[i][0]);
            execvp(commands[i][0],commands[i]);
            perror("Exec failed");
            exit(EXIT_FAILURE);
        }
    }

    //Parent 
    printf("print out history: -------\n");
    while((pid=wait(&status))>0) {
        printf("Child process with PID %d finished\n", pid);
    }
    return EXIT_SUCCESS;

}