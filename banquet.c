/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:12:36 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/19 00:49:44 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	sleeping(t_philo *phi)
{
	if (is_dead(phi))
		return (-1);
	display_banquet(phi, "is sleeping", phi->banquet->t_start);
	ft_usleep(phi);
	display_banquet(phi, "is_thinking", phi->banquet->t_start);
	return (0);
}

int	meal(t_philo *phi)
{
	if (is_dead(phi))
		return (-1);
	pthread_mutex_lock(&phi->banquet->eat);
	phi->last_meal = last_meal_update();
	if (phi->meals_limit > -1)
		phi->meals_limit--;
	pthread_mutex_unlock(&phi->banquet->eat);
	display_banquet(phi, "is eating", phi->banquet->t_start);
	if (!check_death(phi))
		ft_usleep(phi);
	else
	{
		// display_banquet(phi, "END", phi->banquet->t_start);
		return (-1);
	}
	return (0);
}

int	grab_fork(t_philo *phi, long start)
{
	if (is_dead(phi))
		return (-1);
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
		display_banquet(phi, "has taken left fork", start);
		pthread_mutex_lock(phi->left_fork);
		display_banquet(phi, "has taken a right fork", start);
	}
	else
	{
		pthread_mutex_lock(phi->left_fork);
		display_banquet(phi, "has taken left fork", start);
		pthread_mutex_lock(phi->right_fork);
		display_banquet(phi, "has taken a right fork", start);
	}
	return (0);
}

int	drop_fork(t_philo *phi, long start)
{
	if (is_dead(phi))
	{
		pthread_mutex_unlock(phi->left_fork);
		pthread_mutex_unlock(phi->right_fork);
		return (-1);
	}
	display_banquet(phi, "put back left fork", start);
	pthread_mutex_unlock(phi->left_fork);
	display_banquet(phi, "put back right fork", start);
	pthread_mutex_unlock(phi->right_fork);
	return (0);
}

