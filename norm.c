/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:11:23 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/24 02:47:36 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	norm_isdeadboi(t_philo *phi)
{
	if (philo_is_full(phi) < 0)
	{
		pthread_mutex_unlock(&phi->block);
		return (2);
	}
	else if (!phi->banquet->end)
		display_banquet(phi, "died", phi->banquet->t_start);
	pthread_mutex_lock(&phi->banquet->lock);
	phi->banquet->end = 1;
	pthread_mutex_unlock(&phi->banquet->lock);
	pthread_mutex_unlock(&phi->block);
	return (1);
}
