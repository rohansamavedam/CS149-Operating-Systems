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
            char * argv_list[] = {"/sbin/ping","google.com","-t","3",(char*)0};
            int val = execv("/sbin/ping",argv_list);
            printf("%d\n", val);
            exit(0);
            // We get the return code for a process from the wait.
        }
    }
    
        pid_t pid;

        while (waitpid(pid, &status, 0) > 0) {

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

//            // waitpid() failed
//            printf("waitpid() failed\n");
//
//        exit(0);
    return 0;
}
