#include "philo.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

// int			start_ = 0;

// long long	get_time(void)
// {
// 	struct timeval	tv;
// 	long long		time;

// 	gettimeofday(&tv, NULL);
// 	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
// 	return (time);
// }

void	*sleep_(void *s)
{
	return (printf("gg\n"), s);
}

int	main(void)
{
	pthread_t	h;
	memset(&h, 0, sizeof(void *));
	printf("%p\n", h);
	pthread_create(&h, NULL, sleep_, NULL);
	sleep(5);
	printf("hh\n");
	printf("%p\n", h);
	pthread_join(h, NULL);
}
