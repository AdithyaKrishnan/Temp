int main() {
    unsigned int steps = 256 * 1024 * 1024;
    static int arr[4 * 1024 * 1024];
    int lengthMod;
    unsigned int i;
    double timeTaken;
    clock_t start;
    int size; // in KB
    int increment = 16; // +4KB each iteration

    // for each size to test for ... 
    for (size = 4; (size * KB) <= (sizeof(arr)); size += increment) {
	    lengthMod = (size * KB) - 1;
	    start = clock();
	    for (i = 0; i < steps; i++) {
	        arr[(i * 16) & lengthMod]++;
	    }

	    timeTaken = (double)(clock() - start)/CLOCKS_PER_SEC;
	    printf("%d, %.8f \n", (lengthMod+1) / 1024, timeTaken);
    }
}