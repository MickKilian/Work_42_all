#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

int main()
{
	int a = 456;
	int *aa = &a;
	sem_t	*sem_test;
	int	i;
		
	i = 0;
	sem_unlink("/sem_test");
	sem_test = sem_open("sem_test", O_CREAT, 0600, 50);
	if (fork())
	{
		printf("PARENT: %d, %p, %d, %p, %p\n", a, aa, *aa, &a, &aa);
		printf("a: %d, *aa: %d\n", a, *aa);
		while (i <= 5)
		{
			sem_wait(sem_test);
			printf("parent : %d\n", ++i);
			sleep(1);
		}
		wait(NULL);
	}
	else
	{
		a = 22;
		printf("CHILD: %d, %p, %d, %p, %p\n", a, aa, *aa, &a, &aa);
		printf("a: %d, *aa: %d\n", a, *aa);
		while (i <= 5)
		{
			sem_wait(sem_test);
			printf("child : %d\n", ++i);
			sleep(1);
		}
	}
	sem_unlink("/sem_test");
	sem_close(sem_test);
	return (0);
}
