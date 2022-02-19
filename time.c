/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:13:27 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/19 00:47:58 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

long	time_passed(long last)
{
	struct timeval	time;
	long			now;

	gettimeofday(&time, NULL);
	now = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (now - last);
}

long	last_meal_update(void)
{
	struct timeval	time;
	long			now;

	gettimeofday(&time, NULL);
	now = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (now);
}

int	ft_usleep(t_philo *phi)
{
	int	i;
	int	sleep;

	pthread_mutex_lock(&phi->banquet->sleep);
	i = -1;
	sleep = phi->time_to_sleep * 100;
	while (i++ < 10)
	{
		if (check_death(phi))
		{
			pthread_mutex_unlock(&phi->banquet->sleep);
			return (-1);
		}
		if (is_dead(phi))
		{
			pthread_mutex_unlock(&phi->banquet->sleep);
			return (-1);
		}
		usleep(sleep);
	}
	pthread_mutex_unlock(&phi->banquet->sleep);
	return (1);
}

long	init_time(void)
{
	struct timeval	time;
	long			start;

	gettimeofday(&time, NULL);
	start = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (start);
}
