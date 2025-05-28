#include "philo.h"

pthread_mutex_t	*mutex_locker(void)
{
	static pthread_mutex_t	locker;
	static int				i = 0;

	if (i == 0)
	{
		pthread_mutex_init(&locker, NULL);
		i++;
	}
	return (&locker);
}

/*add mutexs adder */

t_mutex *mutexer_create(pthread_mutex_t *mutex){
	t_mutex		*new;
	new = ft_calloc(sizeof(t_mutex), C_ARENA);
	new->locked = true;
	new->mutex = mutex;
	return new;
}

t_locker	*locker_create(pthread_t *t, pthread_mutex_t *mutex)
{
	t_locker	*new;

	new = ft_calloc(sizeof(t_locker), C_ARENA);

	new->owner = t;
	new->mutexs = vector_new(sizeof(t_mutex));
	new->mutexs->push_back(new->mutexs, mutexer_create(mutex));
	return new;
}

t_vector	**locker_head(void)
{
	static t_vector	*locker = NULL;

	if (!locker)
	{
		locker = vector_new(sizeof(t_locker));
	}
	return &locker;
}

int	unlock_state(pthread_t *t, pthread_mutex_t *mutex)
{
	t_locker	*tmp;
	int			i;
	int			j;
	t_vector	*locker;

	locker = *locker_head();
	i = 0;
	j = 0;
	while (i < locker->size)
	{
		if (((t_locker *)(locker->get(locker, i)))->owner == t)
		{
			tmp = (t_locker *)(locker->get(locker, i));
			while (j < tmp->mutexs->size)
			{
				if (((t_mutex *)tmp->mutexs->get(tmp->mutexs,
							j))->mutex == mutex)
				{
					if (((t_mutex *)tmp->mutexs->get(tmp->mutexs,
								j))->locked == false)
						return (false);
					else
						return (true);
				}
				j++;
			}
		}
		i++;
	}
	return (false);
}

int	lock_state(pthread_t *t, pthread_mutex_t *mutex)
{
	t_locker	*tmp = NULL;
	t_vector	*locker;
	t_mutex *tmp2 =NULL;
	int			i;
	int			j;

	locker = *locker_head();
	i = 0;
	j = 0;
	while (i < locker->size)
	{
		if (((t_locker *)(locker->get(locker, i)))->owner == t)
		{
			tmp = (t_locker *)(locker->get(locker, i));
			while (j < tmp->mutexs->size)
			{
				if (((t_mutex *)tmp->mutexs->get(tmp->mutexs,
							j))->mutex == mutex)
				{
					tmp2 = tmp->mutexs->get(tmp->mutexs,j);
					if (tmp2->locked == false)
						return (true);
					else
						return (false);
				}
				j++;
			}
			if (!tmp2){
				tmp->mutexs->push_back(tmp->mutexs, mutexer_create(mutex));
				return true;
			}

		}
		i++;
	}
	if (!tmp){
		locker->push_back(locker, locker_create(t, mutex));
	}
	return true;
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
	// printf("unlock\n");
	return (1);
}

int	mutex_do(int act, pthread_mutex_t *mutex)
{
	// static bool	locked = false;
	int			status;

	status = 1;
	// _lock_(mutex_locker());
	// printf("state = %d %d\n", locked, act);
	if (act == LOCK )
	{
		status = _lock_(mutex);
		// locked = true;
	}
	else if (act == UNLOCK )
	{
		// printf("tt\n");
		status = _unlock_(mutex);
		// _lock_(mutex_locker());
		// locked = false;
	}
	// _unlock_(mutex_locker());
	return ( status);
}
