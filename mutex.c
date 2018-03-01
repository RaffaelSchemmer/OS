/*
 *  unisex/unisex.c
 *
 *	Solution for the unisex bathroom problem using pthreads, mutex
 *	locks and condition variables.
 *  http://cnds.eecs.jacobs-university.de/courses/os-2011/src/unisex/unisex.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <assert.h>
#include <pthread.h>

typedef struct bathroom 
{
    unsigned int    males;
    unsigned int    females;
    unsigned int    total_males;
    unsigned int    total_females;
    pthread_mutex_t mutex;
    pthread_cond_t  full;
} bathroom_t;

static bathroom_t shared_bathroom = {
    .males = 0,
    .females = 0,
    .total_males = 0,
    .total_females = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .full  = PTHREAD_COND_INITIALIZER
};

static const char *progname = "unisex";

static void
use_bathroom(bathroom_t *bathroom, int ms)
{
#ifdef DEBUG
    printf("bathroom: %3d m %3d f %5d m %5d f\n",
	   bathroom->males, bathroom->females,
	   bathroom->total_males, bathroom->total_females);
#endif
    assert(bathroom->females > 0 || bathroom->males > 0);
    assert((bathroom->females == 0 && bathroom->males < 4)
	   ||(bathroom->males == 0 && bathroom->females < 4));
    (void) usleep(1000 * ms);
}

static void enjoy_live(int ms)
{
    (void) usleep(1000 * ms);
}

static void* male(void *data)
{
    bathroom_t *bathroom = (bathroom_t *) data;

    while (1) 
	{
		enjoy_live(100);
        pthread_mutex_lock(&bathroom->mutex);
	
		while (bathroom->females > 0 || bathroom->males > 2) 
		{
            pthread_cond_wait(&bathroom->full, &bathroom->mutex);
		}
	
		bathroom->males++;
        pthread_mutex_unlock(&bathroom->mutex);
		use_bathroom(bathroom, 10);
        pthread_mutex_lock(&bathroom->mutex);
		bathroom->males--;
		bathroom->total_males++;
        pthread_cond_broadcast(&bathroom->full);
        pthread_mutex_unlock(&bathroom->mutex);
    }
	
    return NULL;
}

static void* female(void *data)
{
    bathroom_t *bathroom = (bathroom_t *) data;
        
    while (1) 
	{
	
		enjoy_live(100);
        pthread_mutex_lock(&bathroom->mutex);
		
		while (bathroom->males > 0 || bathroom->females > 2) 
		{
            pthread_cond_wait(&bathroom->full, &bathroom->mutex);
		}
		
		bathroom->females++;
        pthread_mutex_unlock(&bathroom->mutex);
		use_bathroom(bathroom, 15);
        pthread_mutex_lock(&bathroom->mutex);
		bathroom->females--;
		bathroom->total_females++;
        pthread_cond_broadcast(&bathroom->full);
        pthread_mutex_unlock(&bathroom->mutex);
    
	}
    return NULL;
}

static int run(int nm, int nf)
{
    int err, n = nm + nf;
    pthread_t thread[n];

    for (int i = 0; i < n; i++) 
	{
		err = pthread_create(&thread[i], NULL,
	    i < nm ? male : female, &shared_bathroom);
		if (err) 
		{
			fprintf(stderr, "%s: %s: unable to create thread %d: %d\n",
		    progname, __func__, i, err);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < n; i++) 
	{
        if (thread[i]) (void) pthread_join(thread[i], NULL);
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    int c, nm = 1, nf = 1;
    
    while ((c = getopt(argc, argv, "m:f:h")) >= 0) 
	{
        switch (c) 
		{
			case 'm':
			
				if ((nm = atoi(optarg)) <= 0) 
				{
					fprintf(stderr, "number of males must be > 0\n");
					exit(EXIT_FAILURE);
				}
				
            break;
			
			case 'f':
            
				if ((nf = atoi(optarg)) <= 0) 
				{
					fprintf(stderr, "number of females must be > 0\n");
					exit(EXIT_FAILURE);
				}
            
			break;
        
			case 'h':
			
				printf("Usage: %s [-m males] [-f females] [-h]\n", progname);
				exit(EXIT_SUCCESS);
			
			break;
		}
    }

    return run(nm, nf);
}
