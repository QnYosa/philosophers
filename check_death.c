/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:34:47 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/18 23:49:03 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	check_death(t_philo *phi)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&phi->banquet->death);
	ret = phi->banquet->end;
	pthread_mutex_unlock(&phi->banquet->death);
	// display_banquet(phi, "CHECK_DEATH", phi->banquet->t_start);
	return (ret);
}

int	is_dead(t_philo *phi)
{
	long			time_now;
	struct timeval	c_time;

	pthread_mutex_lock(&phi->banquet->death);
	gettimeofday(&c_time, NULL);
	time_now = c_time.tv_usec / 1000 + c_time.tv_sec * 1000;
	// printf("last meal = %ld\n", time_now - phi->last_meal);
	pthread_mutex_lock(&phi->banquet->tlk_stick);
	if (time_now - phi->last_meal >= phi->time_to_die)
	{
		display_banquet(phi, "JE SUIS MORT\n", phi->banquet->t_start);
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
