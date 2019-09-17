#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {

//  A loop to get all the file names from command line.
    char *arr[10];
    int i = 1;
    while(i < argc){
        char * fileName = argv[i];
        arr[i-1] = fileName;
        i++;
    }
    
    int p[2];
    pipe(p);

    double totalTotalSum;

    for(int i = 0; i < argc - 1; i++){
        if(fork() == 0){
//            printf("%s\n", arr[i]);
            double totalSum;
            // Reading and Computing Sum Part
            char * fileName = arr[i];
            FILE * numbersFile = fopen(fileName, "r");
            int numberOfConversionsProcessed;
            numberOfConversionsProcessed = fscanf(numbersFile, "%lf", &totalSum);
            while(numberOfConversionsProcessed == 1){
                double temp;

                numberOfConversionsProcessed = fscanf(numbersFile, "%lf", &temp);

                if(numberOfConversionsProcessed == 1) {
                    totalSum += temp;
                }
            }
            printf("%lf\n", totalSum);
            write(p[1], &totalSum, sizeof(totalSum));
            close(p[1]);
            exit(0);
        }
        double val;
        read(p[0], &val, sizeof(val));
//        printf("%lf\n", val);
        totalTotalSum = totalTotalSum + val;
    }

    printf("%lf\n", totalTotalSum);

    return 0;
}

