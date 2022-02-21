/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:34:47 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/22 00:08:19 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	philo_is_full(t_philo *phi)
{
	pthread_mutex_lock(&phi->banquet->tlk_stick);
	if (phi->meals_limit == 0)
	{
		pthread_mutex_unlock(&phi->banquet->tlk_stick);
		return (-1);
	}
	pthread_mutex_unlock(&phi->banquet->tlk_stick);
	return (0);
}

int	check_death(t_philo *phi)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&phi->banquet->check);
	ret = phi->banquet->end;
	pthread_mutex_unlock(&phi->banquet->check);
	return (ret);
}
