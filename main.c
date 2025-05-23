/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:37:29 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/22 22:44:42 by zdidah           ###   ########.fr       */
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
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].last_eat_time = 0;
		philos[i].data = data;
		i++;
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->start_time = get_time();
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
	data->start_time = get_time();
	pthread_mutex_init(&data->print_, NULL);
	pthread_mutex_init(&data->eat_, NULL);
	pthread_mutex_init(&data->forks_, NULL);
	return (0);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

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

void	thinking(t_data *data, t_philo *p, size_t time)
{
	pthread_mutex_lock(&data->print_);
	printf("%lld %d is thinking\n", get_time() - data->start_time, p->id);
	pthread_mutex_unlock(&data->print_);
	usleep(time * 1000);
}

void sleeping(t_data *data, t_philo *p)
{
	pthread_mutex_lock(&data->print_);
	printf("%lld %d is sleeping\n", get_time() - data->start_time, p->id);
	pthread_mutex_unlock(&data->print_);
	usleep(data->time_to_sleep * 1000);
}

bool *stop_(){
	static bool stop = false;
	return &stop;
}

void *monitor_philos(void *philos)
{
	int i;
	t_philo *p;
	p = (t_philo *)philos;

	while (1)
	{
		i = 0;
		while (i < p->data->philo_count)
		{
			if (p[i].last_eat_time + p->data->time_to_die < get_time() - p->data->start_time)
			{
				pthread_mutex_lock(&p->data->print_);
				printf("%lld %d is dead\n", get_time() - p->data->start_time, i);
				*stop_() = true;
				pthread_mutex_unlock(&p->data->print_);	
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->data->philo_count % 2 == 0)
	{
		while (*stop_() == false)
		{
			pthread_mutex_lock(&p->data->forks_);
			if (p->data->forks && *stop_() == false)
			{
				p->data->forks -= 2;
				pthread_mutex_unlock(&p->data->forks_);
				p->l_fork = 1;
				p->r_fork = 1;
				p_msg(p->data, p->id, "is eating");
				p->last_eat_time = get_time();
				usleep(p->data->time_to_eat * 1000);
				if (*stop_() == false)
					return (NULL);
				p->data->forks += 2;
				p->eat_count++;
				p->l_fork = 0;
				p->r_fork = 0;
				sleeping(p->data, p);
			}
			pthread_mutex_unlock(&p->data->forks_);
			if (!p->data->forks && *stop_() == false)
			{
				if (p->data->time_to_die < p->data->time_to_eat)
					sleeping(p->data, p);
				else{
					thinking(p->data, p, p->data->time_to_eat);
					continue;
				}
			}
			if (p->eat_count == p->data->must_eat_count)
			{
				p_msg(p->data, p->id, "has eaten enough");
				return (NULL);
			}
		}
	}else{
		while (*stop_() == false){
			pthread_mutex_lock(&p->data->forks_);
			if (p->data->forks> 1)
			{
				p->data->forks -= 2;
				pthread_mutex_unlock(&p->data->forks_);
				p->l_fork = 1;
				p->r_fork = 1;
				p_msg(p->data, p->id, "is eating");
				p->last_eat_time = get_time();
				usleep(p->data->time_to_eat * 1000);
				p->data->forks += 2;
				p->eat_count++;
				p_msg(p->data, p->id, "is sleeping");
				usleep(p->data->time_to_sleep * 1000);
			}
			pthread_mutex_unlock(&p->data->forks_);
			if (!p->data->forks || p->data->forks == 1)
			{
				if (p->data->time_to_die < p->data->time_to_eat)
					sleeping(p->data, p);
				else{
					thinking(p->data, p, p->data->time_to_eat);
					continue;
				}
			}
			if (p->eat_count == p->data->must_eat_count)
			{
				pthread_mutex_lock(&p->data->print_);
				printf("%lld %d has eaten enough\n", get_time() - p->data->start_time, p->id);
				pthread_mutex_unlock(&p->data->print_);
				return (NULL);
			}
		}
		
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data data;
	pthread_t monitor;
	int i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (init_data(&data, argc, argv) == -1)
		return (1);
	t_philo philos[data.philo_count];
	init_philos(&data, philos);
	i = 0;
	while (i < data.philo_count)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_philos, philos);
	while(i--)
		pthread_join(philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}