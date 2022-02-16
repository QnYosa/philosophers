/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Crmealed: 2022/02/12 03:37:40 by dimitriyoul       #+#    #+#             */
/*   Updated: 2022/02/13 15:10:25 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	meal(t_philo *phi)
{
	int		i;
	long	time;

	time = time_passed(phi->last_meal);
	if (time >= phi->time_to_die)
		return (-1);
	phi->last_meal = last_meal_actualization();
	i = -1;
	display_banquet(phi, "is eating", phi->banquet->t_start);
	while (++i < 20)
	{
		ft_usleep(phi->time_to_eat);
	}
	return (0);
}

int	grab_fork(t_philo *phi, long start)
{
	// faire comprendre qui prend la fourhette et laquelle ils doivent prendre.
	if (is_dead(phi))
		return (-1);
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
		pthread_mutex_lock(phi->left_fork);
		display_banquet(phi, "has taken left fork", start);
		display_banquet(phi, "has taken a right fork", start);
		meal(phi);
		drop_fork(phi, start);
	}
	else
	{
		pthread_mutex_lock(phi->left_fork);
		pthread_mutex_lock(phi->right_fork);
		display_banquet(phi, "has taken a left fork", start);
		display_banquet(phi, "has taken right fork", start);
		if (meal(phi) < 0)
			return (-1);
		drop_fork(phi, start);
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
