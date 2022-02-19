/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:12:36 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/19 21:48:34 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	sleeping(t_philo *phi)
{
	if (is_dead(phi))
		return (-1);
	display_banquet(phi, "is sleeping", phi->banquet->t_start);
	if (ft_usleep(phi) < 0)
		return (-1);
	display_banquet(phi, "is_thinking", phi->banquet->t_start);
	return (0);
}

int	meal(t_philo *phi)
{
	if (is_dead(phi))
		return (-1);
	pthread_mutex_lock(&phi->banquet->eat);
	display_banquet(phi, "is eating", phi->banquet->t_start);
	if (phi->meals_limit > -1)
		phi->meals_limit--;
	// printf("%ld et id = %d\n", phi->last_meal, phi->no);
	pthread_mutex_unlock(&phi->banquet->eat);
	usleep(phi->time_to_eat * 1000);
	phi->last_meal = last_meal_update();
	return (0);
}

int	grab_fork(t_philo *phi, long start)
{
	// if (is_dead(phi) || check_death(phi))
	// 	return (-1);
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
		// if (!check_death(phi) && !is_dead(phi))
		display_banquet(phi, "has taken left fork", start);
		pthread_mutex_lock(phi->left_fork);
		// if (!check_death(phi) && !is_dead(phi))
		display_banquet(phi, "has taken a right fork", start);
	}
	else
	{
		pthread_mutex_lock(phi->left_fork);
		// if (!check_death(phi) && !is_dead(phi))
		display_banquet(phi, "has taken left fork", start);
		pthread_mutex_lock(phi->right_fork);
		// if (!check_death(phi) && !is_dead(phi))
		display_banquet(phi, "has taken a right fork", start);
	}
	return (0);
}

int	drop_fork(t_philo *phi, long start)
{
	if (is_dead(phi) || check_death(phi))
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

