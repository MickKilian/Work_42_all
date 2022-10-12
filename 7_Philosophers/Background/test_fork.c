#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int a = 456;
	int *aa = &a;
	
	if (fork())
	{
		wait(NULL);
		printf("PARENT: %d, %p, %d, %p, %p\n", a, aa, *aa, &a, &aa);
		printf("a: %d, *aa: %d\n", a, *aa);
	}
	else
	{
		a = 22;
		printf("CHILD: %d, %p, %d, %p, %p\n", a, aa, *aa, &a, &aa);
		printf("a: %d, *aa: %d\n", a, *aa);
	}
}
