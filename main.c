/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:37:29 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/29 17:20:12 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	return (0);
}

void	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		memset(&philos[i], 0, sizeof(t_philo));
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].last_eat_time = get_time();
		i++;
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->philo_count = atoi(argv[1]);
	data->forks = data->philo_count;
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = atoi(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->philo_count <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0 || (argc == 6
			&& data->must_eat_count <= 0))
		return (-1);
	pthread_mutex_init(&data->print_, NULL);
	pthread_mutex_init(&data->eat_, NULL);
	pthread_mutex_init(&data->forks_, NULL);
	mutex_locker();
	return (0);
}

size_t	get_time(void)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (time);
}

int	p_msg(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->print_);
	printf("%lld %d %s\n", get_time() - data->start_time, id, msg);
	pthread_mutex_unlock(&data->print_);
	return (0);
}
t_data	**_data(void)
{
	static t_data	*data = NULL;

	if (!data)
	{
		data = ft_calloc(sizeof(t_data), C_ARENA);
	}
	return (&data);
}

void	thinking(t_philo *p, size_t time)
{
	if (!p->is_thinking)
	{
		p->is_thinking = true;
		pthread_mutex_lock(&p->data->print_);
		printf("%lld %d is thinking\n", get_time() - p->data->start_time,
			p->id);
		pthread_mutex_unlock(&p->data->print_);
		sleep_with_one_eye_open(time);
	}
}

void	sleeping(t_data *data, t_philo *p)
{
	pthread_mutex_lock(&data->print_);
	printf("%lld %d is sleeping\n", get_time() - data->start_time, p->id);
	pthread_mutex_unlock(&data->print_);
	sleep_with_one_eye_open(data->time_to_sleep);
}

int	*stop_(void)
{
	static int	stop = false;

	return (&stop);
}

size_t	get(void *p)
{
	size_t	i;

	pthread_mutex_lock(&(*_data())->forks_);
	i = *(size_t *)p;
	pthread_mutex_unlock(&(*_data())->forks_);
	return (i);
}

void	set(size_t *p, size_t value)
{
	pthread_mutex_lock(&(*_data())->forks_);
	*p = value;
	pthread_mutex_unlock(&(*_data())->forks_);
}

void	*monitor_philos(void *philos)
{
	int		i;
	t_philo	*p;
	int		full;

	p = (t_philo *)philos;
	full = 0;
	while (1)
	{
		i = 0;
		while (i < p->data->philo_count)
		{
			if (get(&p[i].eat_count) == p[i].data->must_eat_count)
				full++;
			if (!get(&p[i].is_eating) && get_time()
				- get(&p[i].last_eat_time) >= p->data->time_to_die)
			{
				printf("t = %lld\n", get_time());
				printf("lm = %lld\n", get(&p[i].last_eat_time));
				printf("tt %lld\n", (get_time() - get(&p[i].last_eat_time)));
				set((size_t *)stop_(), 1), p_msg(p->data, p->id, "deid");
				return (NULL);
			}
			if (full == p[i].data->philo_count)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

void	sleep_with_one_eye_open(int time)
{
	size_t	duration;

	duration = get_time() + time;
	while (1)
	{
		usleep(1);
		if (get_time() >= duration || get(stop_()))
			break ;
	}
}

bool	takefork(t_philo *p)
{
	int	should_eat;

	should_eat = false;
	pthread_mutex_lock(&p->data->eat_);
	if (get(&p->data->forks) > 1)
	{
		set((size_t *)&p->data->forks, get(&p->data->forks) - 2);
		should_eat = true;
	}
	pthread_mutex_unlock(&p->data->eat_);
	if (should_eat)
	{
		p_msg(p->data, p->id, "has taken a fork");
		p_msg(p->data, p->id, "has taken a fork");
	}
	return (should_eat);
}

void	eating(t_philo *p)
{
	set(&p->last_eat_time, get_time());
	p_msg(p->data, p->id, "is eating");
	set((size_t *)&p->is_eating, true);
	sleep_with_one_eye_open(p->data->time_to_eat);
	set((size_t *)&p->data->forks, get(&p->data->forks) + 2);
	set((size_t *)&p->is_eating, false);
	set((size_t *)&p->eat_count, get((size_t *)&p->eat_count) + 1);
	// p->is_thinking = false;
	set((size_t *)&p->is_thinking, false);
}

void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
    return NULL;
	while (get(stop_()) == false)
	{
		if (takefork(p))
		{
			eating(p);
			sleeping(p->data, p);
			// thinking(p, 1);
		}
		if (p->eat_count == p->data->must_eat_count)
			return (NULL);
		if (get(stop_()))
			return (NULL);
		if (get(&p->data->forks) <= 1)
		{
			// thinking(p, p->data->time_to_eat - 5);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data *data = *_data();
	pthread_t monitor;
	int i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (init_data(data, argc, argv) == -1)
		return (printf("Invalid arguments\n"), 1);
	t_philo philos[data->philo_count];
	init_philos(data, philos);
	data->start_time = get_time();
	i = 0;
	pthread_create(&monitor, NULL, monitor_philos, philos);
	while (i < data->philo_count)
	{
        if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
            return (printf("shit\n"), 1);
        printf("%p\n",philos[i].thread);
		i++;
	}
	i = 0;
    pthread_join(monitor, NULL);
	while (i < data->philo_count)
	{
        printf("%p\n",philos[i].thread);
		if (pthread_join(philos[i].thread, NULL))
			return (printf("shiiiit\n"), 1);
		i++;
	}
	return (0);
}