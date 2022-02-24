/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:12:36 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/24 07:45:34 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	sleeping(t_philo *phi)
{
	int	end;

	pthread_mutex_lock(&phi->block);
	pthread_mutex_lock(&phi->banquet->lock);
	end = phi->banquet->end;
	pthread_mutex_unlock(&phi->banquet->lock);
	pthread_mutex_unlock(&phi->block);
	if (!end)
		display_banquet(phi, "is sleeping", phi->banquet->t_start);
	ft_usleep(phi->banquet, phi->time_to_sleep);
	pthread_mutex_lock(&phi->block);
	pthread_mutex_lock(&phi->banquet->lock);
	end = phi->banquet->end;
	pthread_mutex_unlock(&phi->banquet->lock);
	pthread_mutex_unlock(&phi->block);
	if (end)
		return (-1);
	display_banquet(phi, "is thinking", phi->banquet->t_start);
	pthread_mutex_lock(&phi->banquet->lock);
	if (phi->time_to_think == -1)
		usleep(((phi->time_to_eat - phi->time_to_sleep) % 2) * 1000);
	else if (phi->banquet->n_guests % 2 != 0 && phi->time_to_think == -1)
		usleep(500);
	pthread_mutex_unlock(&phi->banquet->lock);
	return (0);
}

int	meal(t_philo *phi)
{
	long	t;

	pthread_mutex_lock(&phi->block);
	pthread_mutex_lock(&phi->banquet->lock);
	t = phi->banquet->end;
	if (!t)
		display_banquet(phi, "is eating", phi->banquet->t_start);
	phi->last_meal = last_meal_update();
	phi->has_eaten_yet = 1;
	if (phi->meals_limit > -1)
		phi->meals_limit--;
	pthread_mutex_unlock(&phi->banquet->lock);
	pthread_mutex_unlock(&phi->block);
	ft_usleep(phi->banquet, phi->time_to_eat);
	usleep(1000);
	pthread_mutex_lock(&phi->block);
	pthread_mutex_unlock(&phi->block);
	return (0);
}

int	grab_fork_2(t_philo *phi)
{
	pthread_mutex_lock(phi->left_fork);
	pthread_mutex_lock(&phi->block);
	pthread_mutex_lock(&phi->banquet->lock);
	if (!phi->banquet->end)
		display_banquet(phi, "has taken a fork", phi->banquet->t_start);
	pthread_mutex_unlock(&phi->banquet->lock);
	pthread_mutex_unlock(&phi->block);
	if (phi->banquet->n_guests == 1)
	{
		pthread_mutex_unlock(&phi->block);
		pthread_mutex_unlock(phi->left_fork);
		return (10);
	}
	pthread_mutex_lock(phi->right_fork);
	pthread_mutex_lock(&phi->block);
	pthread_mutex_lock(&phi->banquet->lock);
	if (!phi->banquet->end)
		display_banquet(phi, "has taken a fork", phi->banquet->t_start);
	pthread_mutex_unlock(&phi->banquet->lock);
	pthread_mutex_unlock(&phi->block);
	return (0);
}

int	grab_fork(t_philo *phi)
{
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
		pthread_mutex_lock(&phi->block);
		pthread_mutex_lock(&phi->banquet->lock);
		if (!phi->banquet->end)
			display_banquet(phi, "has taken a fork", phi->banquet->t_start);
		pthread_mutex_unlock(&phi->banquet->lock);
		pthread_mutex_unlock(&phi->block);
		pthread_mutex_lock(phi->left_fork);
		pthread_mutex_lock(&phi->banquet->lock);
		if (!phi->banquet->end)
			display_banquet(phi, "has taken a fork", phi->banquet->t_start);
		pthread_mutex_unlock(&phi->banquet->lock);
	}
	else
		return (grab_fork_2(phi));
	return (0);
}

int	drop_fork(t_philo *phi)
{
	pthread_mutex_unlock(phi->right_fork);
	pthread_mutex_unlock(phi->left_fork);
	return (0);
}
