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
	{
		// printf("salut %ld\n", time);
		// printf("phi %d is dead\n", phi->no);
		return (-1);
	}
	phi->last_meal = last_meal_actualization();
	i = -1;
	while (++i < 20)
	{
		// printf("salut\n");
		// printf("itadakimasu\n");
		ft_usleep(phi->time_to_eat);
		// ft_putstr_fd("j'ai mange.\n ", 1);
	}
	return (0);
}

int	grab_fork(t_philo *phi, long start)
{
	// faire comprendre qui prend la fourhette et laquelle ils doivent prendre.
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
		// display_banquet(phi, "has taken a right fork\n", start);
	}
	else
	{
		pthread_mutex_lock(phi->left_fork);
		// display_banquet(phi, "has taken a left fork\n", start);
	}
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->left_fork);
		// display_banquet(phi, "has taken left fork\n", start);
		meal(phi);
		drop_fork(phi, start);
		// pthread_mutex_unlock(phi->right_fork);
	}
	else
	{
		pthread_mutex_lock(phi->right_fork);
		if (meal(phi) < 0)
			return (-1);
		// display_banquet(phi, "has taken right fork\n", start);
		drop_fork(phi, start);
		printf("%ld %d %s\n", time_passed(start), phi->no, "str");
		// pthread_mutex_unlock(phi->left_fork);
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
