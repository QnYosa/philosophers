/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:34:47 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/19 21:11:40 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	philo_is_full(t_philo *phi)
{
	pthread_mutex_lock(&phi->banquet->tlk_stick);
	if (phi->meals_limit == 0)
	{
		pthread_mutex_unlock(&phi->banquet->tlk_stick);
		return (-1);
	}
	pthread_mutex_unlock(&phi->banquet->tlk_stick);
	return (0);
}

int	check_death(t_philo *phi)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&phi->banquet->check);
	ret = phi->banquet->end;
	pthread_mutex_unlock(&phi->banquet->check);
	return (ret);
}

int	is_dead(t_philo *phi)
{
	long			time_now;
	struct timeval	c_time;

	pthread_mutex_lock(&phi->banquet->death);
	gettimeofday(&c_time, NULL);
	time_now = c_time.tv_usec / 1000 + c_time.tv_sec * 1000;
	pthread_mutex_lock(&phi->banquet->tlk_stick);
	if (time_now - phi->last_meal >= phi->time_to_die)
	{
		// if (phi->banquet->end == 0)
		display_banquet(phi, "died\n", phi->banquet->t_start);
		pthread_mutex_lock(&phi->banquet->mutex);
		phi->banquet->end = 1;
		pthread_mutex_unlock(&phi->banquet->mutex);
		pthread_mutex_unlock(&phi->banquet->tlk_stick);
		pthread_mutex_unlock(&phi->banquet->death);
		return (1);
	}
	pthread_mutex_unlock(&phi->banquet->tlk_stick);
	pthread_mutex_unlock(&phi->banquet->death);
	return (0);
}
