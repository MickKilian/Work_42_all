#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#ifndef NUM_THREADS
#define NUM_THREADS 2
#endif

int shared = 0;
//pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

int	ft_definemutex(int	*n)
{
	pthread_mutex_t	mutex;
	int				i;

	i = 0;
	mutex = malloc(NUM_THREADS * siweof(pthread_mutex_t));
	while(i < n)
	{
		mutex[i] = PTHREAD_MUTEX_INITIALIZER;
		i++;
	}
	return (0);
}

void *func1(void* param)
{
	(void)param;
    pthread_mutex_lock(&mutex1);
    printf("Thread 1 is counting down...\n");
	sleep(5);
    pthread_mutex_unlock(&mutex1);
    return 0;
}

void *func2(void* param)
{
	(void)param;
    printf("Thread 2 will start when thread 1 is finished counting down\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 2 started...\n");
    pthread_mutex_unlock(&mutex1);
    return 0;
}

/*void *func3(void* param)
{
	(void)param;
    pthread_mutex_lock(&mutex[1]);
    pthread_mutex_lock(&mutex[2]);
	sleep(2);
    printf("Incrementing the shared variable...\n");
    for (int i = 0; i < 10000; ++i) {
        shared += 1;
    }
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return 0;
}*/

int main()
{
	ft_definemutex(NUM_THREADS);
    pthread_t threads[NUM_THREADS];

//    for (int i = 0; i < NUM_THREADS; ++i) {
//        pthread_create(&threads[i], NULL, func3, NULL);
//   }

    pthread_create(&threads[1], NULL, func1, NULL);
    pthread_create(&threads[2], NULL, func2, NULL);

    for (int i = 0; i < NUM_THREADS; ++i) {
       pthread_join(threads[i], NULL);
    }

    //printf("%d\n", shared);
    exit(EXIT_SUCCESS);
}
