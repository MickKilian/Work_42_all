/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 01:33:35 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/18 01:35:09 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif

int shared = 0;

void *func3(void* param)
{
	(void)param;
    printf("Incrementing the shared variable...\n");
    for (int i = 0; i < 10000; ++i) {
        shared += 1;
    }
    return 0;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, func3, NULL);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("%d\n", shared);
    exit(EXIT_SUCCESS);
}
