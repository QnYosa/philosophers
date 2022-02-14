/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:13:27 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/13 18:09:48 by dyoula           ###   ########.fr       */
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

long	last_meal_actualization(void)
{
	struct timeval	time;
	long			now;

	gettimeofday(&time, NULL);
	now = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (now);
}

void	ft_usleep(int sleep)
{
	int	minus;
	int	i;

	i = -1;
	minus = sleep / 10;
	while (++i < 10)
		usleep(minus);
}

long	init_time(void)
{
	struct timeval	time;
	long			start;

	gettimeofday(&time, NULL);
	start = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (start);
}

int	is_dead(t_philo *phi)
{
	long			time_now;
	struct	timeval	c_time;

	gettimeofday(&c_time, NULL);
	time_now = c_time.tv_usec / 1000 + c_time.tv_sec * 1000;
	pthread_mutex_lock(&phi->banquet->tlk_stick);
	// printf("result =  %ld\n",time_now - phi->last_meal);
	if (time_now - phi->last_meal > phi->time_to_die)
	{
		display_banquet(phi, "philo died\n", phi->banquet->t_start);
		return (1);
	}
	pthread_mutex_unlock(&phi->banquet->tlk_stick);
	return (0);
}
