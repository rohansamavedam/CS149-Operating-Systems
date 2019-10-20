#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *arr[10];
    int i = 1;

    int status;

    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();
        if(pid == 0){
            char * argv_list[] = {"/bin/ls",(char*)0};
            int val = execv("/bin/ls",argv_list);
            printf("%d\n", val);
            exit(0);
            // We get the return code for a process from the wait.
        }
    }

    pid_t pid;

    // Wait will return a code and thats wat we are supposed to returning as exit code.
    // We also need to deal with cating a new err and out files.
    // Check out how to use malloc or calloc.
    // Figure out spwanning too fast thing.
    // based on pid array and args array figure out which programs to run again.
    // WWhen restarted make sure to update the pid of that process again.

    while (waitpid(pid, &status, 0) > 0) {
        printf("%d\n", status);
        if (WIFEXITED(status) && !WEXITSTATUS(status))
            printf("program execution successfull\n");

        else if (WIFEXITED(status) && WEXITSTATUS(status)) {
            if (WEXITSTATUS(status) == 127) {

                // execv failed
                printf("execv failed\n");
            }
            else
                printf("program terminated normally,"
                       " but returned a non-zero status\n");
        }
        else
            printf("program didn't terminate normally\n");
    }

    return 0;
}
