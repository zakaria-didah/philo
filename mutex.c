#include "philo.h"

pthread_mutex_t	*mutex_locker(void)
{
	static pthread_mutex_t	locker;
	static int				i = 0;

	if (!i && pthread_mutex_init(&locker, NULL))
		i++;
	return (&locker);
}

int	_lock_(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		return (printf("can't lock mutex %p\n", mutex), 0);
	return (1);
}
int	_unlock_(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
		return (printf("can't unlock mutex %p\n", mutex), 0);
	return (1);
}

int	mutex_do(t_mutex act, pthread_mutex_t *mutex)
{
	static bool	locked = false;
    int status = 1;

	_lock_(mutex_locker());
	if (act == LOCK && !locked)
	{
		status = _lock_(mutex);
		locked = true;
		return (_unlock_(mutex_locker()), status);
	}
	else if (act == UNLOCK && locked)
	{
		status = pthread_mutex_unlock(mutex);
		locked = false;
		return (_unlock_(mutex_locker()), status);
	}
	return (_unlock_(mutex_locker()),status );
}
