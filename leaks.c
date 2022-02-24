/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:50:03 by dimitriyoul       #+#    #+#             */
/*   Updated: 2022/02/23 17:34:33 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	leaks_maestro(t_banquet *banquet)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&banquet->mutex);
	pthread_mutex_destroy(&banquet->tlk_stick);
	pthread_mutex_destroy(&banquet->display);
	pthread_mutex_destroy(&banquet->death);
	pthread_mutex_destroy(&banquet->eat);
	pthread_mutex_destroy(&banquet->sleep);
	pthread_mutex_destroy(&banquet->lock);
	while (++i < banquet->n_guests)
		pthread_mutex_destroy(banquet->forks + i);
	free(banquet->guests);
	free(banquet->forks);
	return (0);
}
