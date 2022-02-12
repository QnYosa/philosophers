/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 03:10:22 by dimitriyoul       #+#    #+#             */
/*   Updated: 2022/02/12 03:25:21 by dimitriyoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	display_banquet(t_philo *phi, char *str)
{
	pthread_mutex_lock(&phi->banquet->mutex);
	printf("%d %d %s\n", 0, phi->no, str);
	pthread_mutex_unlock(&phi->banquet->mutex);
}
