/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:13:27 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/17 23:17:18 by dyoula           ###   ########.fr       */
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

void	ft_usleep(int sleep)
{
	int	minus;

	minus = sleep * 1000;
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

int	check_death(t_philo *phi)
{
	pthread_mutex_lock(&phi->banquet->mutex);
	if (!phi->banquet->end)
	{
		// display_banquet(phi, "je continue personne n'est mort", phi->banquet->t_start);
		pthread_mutex_unlock(&phi->banquet->mutex);
		return (1);
	}
	else
	{
		// display_banquet(phi, "qqn est mort", phi->banquet->t_start);
		pthread_mutex_unlock(&phi->banquet->mutex);
		return (-1);
	}
}

int	is_dead(t_philo *phi)
{
	long			time_now;
	struct timeval	c_time;

	gettimeofday(&c_time, NULL);
	time_now = c_time.tv_usec / 1000 + c_time.tv_sec * 1000;
	pthread_mutex_lock(&phi->banquet->tlk_stick);
	if (time_now - phi->last_meal >= phi->time_to_die)
	{
		pthread_mutex_unlock(&phi->banquet->tlk_stick);	
		// if (phi->banquet->end == 0)
		display_banquet(phi, "philo died\n", phi->banquet->t_start);
		pthread_mutex_lock(&phi->banquet->mutex);
		phi->banquet->end = 1;
		pthread_mutex_unlock(&phi->banquet->mutex);
		return (1);
	}
	pthread_mutex_unlock(&phi->banquet->tlk_stick);
	return (0);
}
