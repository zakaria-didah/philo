/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:38:10 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/28 22:49:28 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "garb/garb.h"
# include "vector.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				forks;
	long long		start_time;
	bool			stop;
	pthread_mutex_t	print_;
	pthread_mutex_t	eat_;
	pthread_mutex_t	forks_;
}					t_data;

typedef struct s_mutex
{
	pthread_mutex_t	*mutex;
	bool			locked;
}					t_mutex;


typedef struct s_locker
{
	pthread_t		*owner;
	t_vector		*mutexs;
}					t_locker;

typedef enum
{
	LOCK,
	UNLOCK
}					locks;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_eat_time;
	pthread_t		thread;
	int				l_fork;
	int				r_fork;
	struct s_data	*data;
}					t_philo;

long long			get_time(void);
t_data				**_data(void);
void				*ft_memmove(void *dst, const void *src, size_t len);
/*act is the act you perform on the mutex it either can equal LOCK or UNLOCK*/
int					mutex_do(int act, pthread_mutex_t *mutex);
/*should be called in the main thread to init the mutex_do func.*/
pthread_mutex_t		*mutex_locker(void);
void sleep_with_one_eye_open(int time);
#endif