/*
To determine the L1 and L2 cache miss penalties, the approach here is to try to access
the caches in terms of the respective cache lines, and make sure that each access is a
miss. (These programs actually measure the miss latency.
Miss penalty will be latency - hittime. Measuring hittime is trivial.)
*/

#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#define PAGE_SIZE 8192
#define L1_CACHE_LINE_SIZE 32
#define L1_CACHE_SIZE 16384 //32768

main(int argc, char *argv[])
{
    float total_time;
    int num_accesses;
    register int *a, *b, i, num_iter, k, l;
    struct timeval t1, t2;

    num_iter = 1024;
    b = a = (void *) sbrk(2 * L1_CACHE_SIZE);

    /* Touch all pages */
    for(k = 0; k < 2 * L1_CACHE_SIZE/PAGE_SIZE; k++, a += 2048)
        i = *a;

    gettimeofday(&t1,0);

    for(a = b,k = 0; k < num_iter; k++, a = b)
	{
        /* Alternate accesses to blocks of data, each of size = L1_CACHE_SIZE.
	   These blocks mutually knock each other out of the L1 cache,
	    resulting in L1 cache misses for every access */
        /* Each iteration in the loop accesses one cache line */
        for(l = 0; l < L1_CACHE_SIZE/L1_CACHE_LINE_SIZE; l++,a += 8)
            i = *a;

        for(l = 0; l < L1_CACHE_SIZE/L1_CACHE_LINE_SIZE; l++,a += 8)
            i = *a;
    }

    gettimeofday(&t2,0);

    total_time = ((t2.tv_sec-t1.tv_sec)*1000000 + (t2.tv_usec-t1.tv_usec));
    num_accesses = num_iter * (L1_CACHE_SIZE/L1_CACHE_LINE_SIZE) * 2.0;
    printf("L1 cache miss latency: %f microseconds\n", total_time/num_accesses);
}
