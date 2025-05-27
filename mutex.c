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

t_locker	*add(pthread_t *t, pthread_mutex_t *mutex)
{
	t_locker	*new;
	t_mutex		*_new_;

	new = ft_calloc(sizeof(t_locker), C_ARENA);
	_new_ = ft_calloc(sizeof(t_mutex), C_ARENA);
	_new_->locked = false;
	_new_->mutex = mutex;
	new->owner = t;
	new->mutexs = vector_new(sizeof(t_mutex));
	new->mutexs->push_back(new->mutexs, _new_);
}

t_vector	*locker_head(void)
{
	static t_vector	*locker = NULL;

	if (!locker)
	{
		locker = vector_new(sizeof(t_locker));
	}
}

int	locker_init(pthread_t *t, pthread_mutex_t *mutex)
{
	t_locker	*tmp;
	int			i;
	int			j;
	t_vector	*locker;

	locker = locker_head();
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
			/*check for mutex if is in the owner if not add it*/
		}
		i++;
	}
	return (false);
}

int	mutex_state(pthread_t *t, pthread_mutex_t *mutex)
{
	t_locker	*tmp = NULL;
	t_vector	*locker;
	t_mutex *tmp2 =NULL;
	int			i;
	int			j;

	locker = locker_head();
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
						return (false);
					else
						return (true);
				}
				j++;
			}

		}
		i++;
	}
	if (!tmp){
		locker->push_back(locker, add(t, mutex));
	}
}

int	_lock_(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		return (printf("can't lock mutex %p\n", mutex), 0);
	printf("lock\n");
	return (1);
}

int	_unlock_(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
		return (printf("can't unlock mutex %p\n", mutex), 0);
	printf("unlock\n");
	return (1);
}

int	mutex_do(int act, pthread_t *t, pthread_mutex_t *mutex)
{
	static bool	locked = false;
	int			status;

	status = 1;
	if (act == LOCK && !locked)
	{
		status = _lock_(mutex);
		_lock_(mutex_locker());
		locked = true;
	}
	else if (act == UNLOCK && locked)
	{
		status = _unlock_(mutex);
		_lock_(mutex_locker());
		locked = false;
	}
	return (_unlock_(mutex_locker()), status);
}
