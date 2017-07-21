/*
C program to measure the size of L1 cache - using conflict misses. Here, the 
approach is to generate accesses so that the same instruction generates accesses 
to addresses that map to the same location in cache. Addresses that are "cache size"
apart will have this property. Two important assumptions for this program to work
are that the cache is direct mapped and virtually addressed. 
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PAGES 1024
#define MAX_GUESS 128*1024

double time_elapsed(struct timespec start, struct timespec end);
struct timespec start,end;
int main() 
{
    volatile char *a;
    register int pagesize, i, incr;
    //struct timespec start, end;
    long long int calc;

    pagesize = sysconf(_SC_PAGESIZE);

    printf("PAGESIZE = %d\n", pagesize);

    a = (char *) memalign(pagesize, pagesize*NUM_PAGES);

    for (i=0; i < NUM_PAGES; i++) a[pagesize*i] = 0;

    for(incr=1; incr < MAX_GUESS; incr*=2)
    {
        //start = gettime();
        clock_gettime(CLOCK_REALTIME, start);
	for(i=pagesize*NUM_PAGES/4; i<pagesize*(NUM_PAGES/4 + 1); i++)
            a[i] += a[i+incr];
        //end = gettime();
        clock_gettime(CLOCK_REALTIME, end);
	calc = (time_elapsed(start,end)) / (pagesize);
        printf("Avg time (%d accesses, incr = %d) = %lld nsec\n", pagesize, incr, calc);
        usleep(1000);
    }
    return 0; 
}
double time_elapsed(struct timespec start, struct timespec end)
{
	double t;
	t=(end.tv_sec-start.tv_sec)*1000;
	t+=(end.tv_nsec-start.tv_nsec)*0.000001;
	return t;
}
