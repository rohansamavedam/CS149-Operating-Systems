// Krishna Rohan Samavedam, CS149 SECTION 01, FALL 2019

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double calculateSumInSingleFile(char *fileName){
    FILE * numbersFile = fopen(fileName, "r");

    double totalSum;

    if (numbersFile == NULL){
        printf("Error: File %s Not Found\n", fileName);
        return 0;
    }

    int numberOfConversionsProcessed;
    numberOfConversionsProcessed = fscanf(numbersFile, "%lf", &totalSum);

    while(numberOfConversionsProcessed == 1){
        double temp;

        numberOfConversionsProcessed = fscanf(numbersFile, "%lf", &temp);

        if(numberOfConversionsProcessed == 1) {
            totalSum += temp;
        }
    }

    return totalSum;
}

int main(int argc, char **argv) {

    // Looping through the command line arguments and adding file names to an array.
    char *arr[10];
    int i = 1;
    while(i < argc){
        char * fileName = argv[i];
        arr[i-1] = fileName;
        i++;
    }

    // Declaring a pipe.
    int p[2];
    pipe(p);

    double totalTotalSum;

    for(int i = 0; i < argc - 1; i++){

        if(fork() == 0){
            // Calling the Single File Sum method that returns the sum of elements of each file.
            char * fileName = arr[i];
            double totalSum = calculateSumInSingleFile(fileName);

            // Writing the Total Sum of the File to Parent Process.
            write(p[1], &totalSum, sizeof(totalSum));
            close(p[1]);
            exit(0);
        }

        // Parent process reading the value from child.
        double val;
        read(p[0], &val, sizeof(val));
        totalTotalSum = totalTotalSum + val;
    }

    printf("%lf\n", totalTotalSum);

    return 0;
}

