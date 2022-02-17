/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:12:36 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/17 19:08:13 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	sleeping(t_philo *phi)
{
	display_banquet(phi, "is sleeping", phi->banquet->t_start);
	ft_usleep(phi->time_to_sleep);
	display_banquet(phi, "is_thinking", phi->banquet->t_start);
	return (0);
}

int	meal(t_philo *phi)
{
	long	time;

	time = time_passed(phi->last_meal);
	if (time >= phi->time_to_die)
		return (-1);
	phi->last_meal = last_meal_update();
	display_banquet(phi, "is eating", phi->banquet->t_start);
	ft_usleep(phi->time_to_eat);
	return (0);
}

int	grab_fork(t_philo *phi, long start)
{
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
		display_banquet(phi, "has taken left fork", start);
		pthread_mutex_lock(phi->left_fork);
		display_banquet(phi, "has taken a right fork", start);
		if (meal(phi) < 0)
		{
			drop_fork(phi, start);
			return (-1);
		}
		drop_fork(phi, start);
		sleeping(phi);
	}
	else
	{
		pthread_mutex_lock(phi->left_fork);
		pthread_mutex_lock(phi->right_fork);
		display_banquet(phi, "has taken right fork", start);
		display_banquet(phi, "has taken a left fork", start);
		if (meal(phi) < 0)
		{
			drop_fork(phi, start);
			return (-1);
		}
		drop_fork(phi, start);
		sleeping(phi);
	}
	return (0);
}

int	drop_fork(t_philo *phi, long start)
{
	(void)start;
	// display_banquet(phi, "put back left fork", start);
	pthread_mutex_unlock(phi->left_fork);
	// display_banquet(phi, "put back right fork", start);
	pthread_mutex_unlock(phi->right_fork);
	return (0);
}
