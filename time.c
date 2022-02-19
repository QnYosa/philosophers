/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:13:27 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/19 21:47:55 by dyoula           ###   ########.fr       */
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

int	ft_usleep_eat(t_philo *phi)
{
	int	i;
	int	sleep;

	i = -1;
	sleep = phi->time_to_sleep * 100;
	while (i++ < 10)
	{
		// if (check_death(phi))
		// 	return (-1);
		// if (is_dead(phi))
		// 	return (-1);
		usleep(sleep);
	}
	return (1);
}

int	ft_usleep(t_philo *phi)
{
	int	i;
	int	sleep;

	i = -1;
	sleep = phi->time_to_sleep * 100;
	while (i++ < 10)
	{
		if (check_death(phi))
			return (-1);
		if (is_dead(phi))
			return (-1);
		usleep(sleep);
	}
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
