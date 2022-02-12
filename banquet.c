/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 03:37:40 by dimitriyoul       #+#    #+#             */
/*   Updated: 2022/02/12 03:41:18 by dimitriyoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	eat(t_philo *phi)
{
	usleep(5000);
}
int	grab_fork(t_philo *phi)
{
	// faire comprendre qui prend la fourhette et laquelle ils doivent prendre.
	if (phi->no % 2 == 0)
	{
		pthread_mutex_lock(phi->right_fork);
		display_banquet(phi, "has taken a right fork");
		// printf("j'ai attrape une right fork \n");
		// printf("je suis philo numero %d\n", phi->no);
	}
	else
	{
		pthread_mutex_lock(phi->left_fork);
		display_banquet(phi, "has taken a left fork");
		// printf("j'ai attrape une left fork \n");
		// printf("je suis philo numero %d\n", phi->no);
	}
	if (phi->no % 2 == 0)
	{
		// printf("j'ai lache une fourchette\n");
		pthread_mutex_lock(phi->left_fork);
		display_banquet(phi, "has taken left fork");
		// pthread_mutex_unlock(phi->right_fork);
		
	}
	else
	{
		// printf("j'ai lache une fourchette\n");
		pthread_mutex_lock(phi->right_fork);
		display_banquet(phi, "has taken right fork");
		// pthread_mutex_unlock(phi->left_fork);
	}
	return (0);
}
