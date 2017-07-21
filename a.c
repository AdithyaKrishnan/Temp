/*
C program to measure the size of L1 and L2 caches - using capacity misses.

To determine the cache size, the approach here is to try to access blocks
of data of increasing size until the size becomes greater than the L1/L2
cache size. We notice a jump in the access times when we cross these
boundaries(L1 and L2 cache sizes).

Accesses must be done in terms of cache lines. The cache line size also
can be determined by accessing strides of various lengths. When one crosses
the size of the cache line, a difference in the access time can be noticed. 
I'm assuming a cache line size of 32 bytes for the L1 cache and 64 bytes for L2.

The following program determines the L1 & L2 cache sizes using capacity misses. 
Run the following program multiple times, each time with a different guess for 
the number of cache lines. Figure out the cache sizes by noticing a jump in the 
access times. For example, if you increase the guess by a factor of two each time,
you'll see a jump(by more than a factor of two) when you cross the cache sizes. 
The program assumes that the cache is split (i.e. there are separate data and 
instruction caches). Click here to see the output and results.
*/

#include <sys/time.h>
#define PAGE_SIZE 8192
#define TOTAL_MEM_SIZE (4096 * 1024)
#define L1_CACHE_LINE_SIZE 32 

main(int argc, char *argv[]) 
{
    float total_time;
    register int *a, *b, i, num_cache_lines_guess, num_iter, k, l;
    struct timeval t1, t2;

    if(argc < 2) 
	{
        printf("Usage: %s guess_num_cache_lines\n", argv[0]);
        exit(1);
    }

    num_cache_lines_guess = atoi(argv[1]);
    b = a = (void *) sbrk(TOTAL_MEM_SIZE);

    /* Touch all pages */
    for(k = 0; k < TOTAL_MEM_SIZE/PAGE_SIZE; k++, a += 2048)
        *a = 1;

    num_iter = TOTAL_MEM_SIZE / (num_cache_lines_guess * L1_CACHE_LINE_SIZE); 

    gettimeofday(&t1,0);

    for(a = b,k = 0; k < num_iter; k++, a = b) 
	{
        /* Each iteration in the loop accesses one cache line */
        for(l = 0; l < num_cache_lines_guess; l++,a += 8)
            i = *a;
    }

    gettimeofday(&t2,0);

    total_time = ((t2.tv_sec-t1.tv_sec)*1000000 + (t2.tv_usec-t1.tv_usec));
    printf("Access time for block of size %d : %f microseconds\n",
    num_cache_lines_guess * L1_CACHE_LINE_SIZE, total_time/num_iter);

}

