/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 00:01:45 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/04 00:14:43 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	init_struct(int ac, char **av, t_banquet *banquet)
{
	banquet->ac = ac;
	banquet->n_philo = ft_atoi(av[1]);
	banquet->time_to_die = ft_atoi(av[2]);
	banquet->time_to_eat = ft_atoi(av[3]);
	banquet->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		banquet->meals_limit = ft_atoi(av[5]);
}
