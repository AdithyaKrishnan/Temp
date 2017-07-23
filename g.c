#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define KB 1024
#define MB 1024 * 1024

int main() {
    unsigned int steps = 512 * 1024 * 1024;
    static int arr[4 * 1024 * 1024];
    int lengthMod = 512 * KB - 1;
    unsigned int i;
    double timeTaken;
    clock_t start;

    start = clock();
    for (i = 0; i < steps; i++) {
        arr[(i * 16) & lengthMod] *= 10;
        arr[(i * 16) & lengthMod] /= 10;
    }
    timeTaken = (double)(clock() - start)/CLOCKS_PER_SEC;
    printf("%d, %.8f \n", (lengthMod+1)/ 1024, timeTaken);

    return 0;
}