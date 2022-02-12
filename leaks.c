/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:50:03 by dimitriyoul       #+#    #+#             */
/*   Updated: 2022/02/12 00:53:48 by dimitriyoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	leaks_maestro(t_banquet *banquet)
{
	int	i;

	i = -1;
	while (++i)
		pthread_mutex_destroy(banquet->forks + i);
	return (0);
}
