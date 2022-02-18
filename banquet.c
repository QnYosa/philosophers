/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:12:36 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/18 23:44:02 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"


int	meal(t_philo *phi)
{
	// long	time;

	// pthread_mutex_lock(&phi->banquet->eat);
	// time = time_passed(phi->last_meal);
	// if (time >= phi->time_to_die)
	// {
	// 	pthread_mutex_unlock(&phi->banquet->eat);
	// 	return (-1);
	// }
	// pthread_mutex_unlock(&phi->banquet->eat);
	// printf("coucou\n");
	if (is_dead(phi))
		return (-1);
	pthread_mutex_lock(&phi->banquet->eat);
	phi->last_meal = last_meal_update();
	pthread_mutex_unlock(&phi->banquet->eat);
	display_banquet(phi, "is eating", phi->banquet->t_start);
	if (!check_death(phi))
		ft_usleep(phi->time_to_eat);
	else
	{
		display_banquet(phi, "END", phi->banquet->t_start);	
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
	// usleep(100000);
	return (0);
}

