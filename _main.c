// #include "philo.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

int			start_ = 0;

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (time);
}

void	sleep_with_one_eye_open(int time)
{
	int	duration;

	duration = get_time() + time;
	while (1)
	{
		usleep(1);
		if (get_time() == duration || get(stop_()))
			break ;
	}
}

int	main(void)
{
	start_ = get_time();
	sleep_with_one_eye_open(60 * 1000);
}
