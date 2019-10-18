#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

/*
 * add floating point numbers in the files passed on the commandline in
 * parallel. a subprocess is created for each commandline argument.
 */
double addup(const char *filename)
{
    double d;
    double sum = 0;
    FILE *fh = fopen(filename, "r");
    if (fh == NULL) {
       perror(filename);
       return 0;
    }
    while (fscanf(fh, "%lf", &d) == 1) {
       sum += d;
    }
    fclose(fh);
    return sum;
}

int main(int argc, char **argv)
{
    double total = 0;
    int fds[2];
    pipe(fds);
    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
	//printf("created %d for %s\n", pid, argv[i]);
        if (pid == 0) {
            double d = addup(argv[i]);
            write(fds[1], &d, sizeof(d));
            exit(0);
        }
        if (pid == -1) {
            // should never happen, but just in case...
            perror("fork");
        }
    }

    // the parent is not going to write anything
    close(fds[1]);
    int wstatus;
    pid_t pid;
    while ((pid = wait(&wstatus)) != -1) {
	if (!WIFEXITED(wstatus)) {
	    // child crashes can be invisible, so track here
	    printf("%d exited abnormally\n", pid);
	}
        double d;
        if (read(fds[0], &d, sizeof d) != sizeof d) {
            // this shouldn't happen either...
            perror("short read");
        } else {
            total += d;
        }
    }
    printf("%lf\n", total);
    return 0;
}
