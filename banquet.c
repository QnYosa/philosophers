/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:12:36 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/21 23:21:52 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	sleeping(t_philo *phi)
{
	pthread_mutex_lock(&phi->banquet->check);
	if (!phi->banquet->end)
		display_banquet(phi, "is sleeping", phi->banquet->t_start);
	pthread_mutex_unlock(&phi->banquet->check);
	ft_usleep(phi->banquet, phi->time_to_sleep);
	pthread_mutex_lock(&phi->banquet->check);
	if (!phi->banquet->end)
		display_banquet(phi, "is thinking", phi->banquet->t_start);
	pthread_mutex_unlock(&phi->banquet->check);
	return (0);
}

int	meal(t_philo *phi)
{
	pthread_mutex_lock(&phi->banquet->check);
	if (!phi->banquet->end)
		display_banquet(phi, "is eating", phi->banquet->t_start);
	if (phi->meals_limit > -1)
		phi->meals_limit--;
	pthread_mutex_unlock(&phi->banquet->check);
	pthread_mutex_lock(&phi->banquet->eat);
	phi->last_meal = init_time(phi->banquet);
	pthread_mutex_unlock(&phi->banquet->eat);
	ft_usleep(phi->banquet, phi->time_to_eat);
	return (0);
}

int	grab_fork(t_philo *phi)
{
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
		pthread_mutex_lock(&phi->banquet->check);
		if (!phi->banquet->end)
			display_banquet(phi, "has taken a fork", phi->banquet->t_start);
		pthread_mutex_unlock(&phi->banquet->check);
		pthread_mutex_lock(phi->left_fork);
		pthread_mutex_lock(&phi->banquet->check);
		if (!phi->banquet->end)
			display_banquet(phi, "has taken a fork", phi->banquet->t_start);
		pthread_mutex_unlock(&phi->banquet->check);
	}
	else
	{
		pthread_mutex_lock(phi->left_fork);
		pthread_mutex_lock(&phi->banquet->check);
		if (!phi->banquet->end)
			display_banquet(phi, "has taken a fork", phi->banquet->t_start);
		pthread_mutex_unlock(&phi->banquet->check);
		if (phi->banquet->n_guests == 1)
		{
			pthread_mutex_unlock(phi->left_fork);
			return (10);
		}
		pthread_mutex_lock(phi->right_fork);
		pthread_mutex_lock(&phi->banquet->check);
		if (!phi->banquet->end)
			display_banquet(phi, "has taken a fork", phi->banquet->t_start);
		pthread_mutex_unlock(&phi->banquet->check);
	}
	return (0);
}

int	drop_fork(t_philo *phi)
{
	pthread_mutex_unlock(phi->right_fork);
	pthread_mutex_unlock(phi->left_fork);
	return (0);
}
