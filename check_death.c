/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:34:47 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/22 23:54:29 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

long	current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

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

int	is_dead(t_philo *phi)
{
	long			now;
	long			difference;

	now = init_time(phi->banquet);
	difference = now - phi->last_meal;
	if (difference >= phi->time_to_die)
	{
		pthread_mutex_lock(&phi->banquet->death);
		phi->banquet->end = 1;
		pthread_mutex_unlock(&phi->banquet->death);
		return (1);
	}
	return (0);
}

int	check_death(t_philo *phi)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&phi->banquet->death);
	ret = phi->banquet->end;
	pthread_mutex_unlock(&phi->banquet->death);
	// printf("%d == RET : %d\n", phi->no, ret);
	return (ret);
}
