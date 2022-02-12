/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 03:37:40 by dimitriyoul       #+#    #+#             */
/*   Updated: 2022/02/13 00:45:34 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	eat(t_philo *phi)
{
	int	i;

	(void)phi;
	i = -1;
	while (++i < 20)
	{
		printf("salut\n");
		usleep(5000000);
		printf("itadakimasu\n");
	}
	ft_putstr_fd("je mange \n ", 1);
	return (0);
}

int	grab_fork(t_philo *phi)
{
	// faire comprendre qui prend la fourhette et laquelle ils doivent prendre.
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
		display_banquet(phi, "has taken a right fork\n");
		// printf("j'ai attrape une right fork \n");
		// printf("je suis philo numero %d\n", phi->no);
	}
	else
	{
		pthread_mutex_lock(phi->left_fork);
		display_banquet(phi, "has taken a left fork\n");
		// printf("j'ai attrape une left fork \n");
		// printf("je suis philo numero %d\n", phi->no);
	}
	if (phi->no % 2 == 0)
	{
		// printf("j'ai lache une fourchette\n");
		pthread_mutex_lock(phi->left_fork);
		display_banquet(phi, "has taken left fork\n");
		eat(phi);
		display_banquet(phi, "has taken right fork\n");
		release_fork(phi);
		// pthread_mutex_unlock(phi->right_fork);
		
	}
	else
	{
		// printf("j'ai lache une fourchette\n");
		pthread_mutex_lock(phi->right_fork);
		eat(phi);
		display_banquet(phi, "has taken right fork\n");
		release_fork(phi);
		// pthread_mutex_unlock(phi->left_fork);
	}
	return (0);
}

int	release_fork(t_philo *phi)
{
	display_banquet(phi, "put back left fork");
	pthread_mutex_unlock(phi->left_fork);
	display_banquet(phi, "put back right fork");
	pthread_mutex_unlock(phi->right_fork);
	return (0);
}
