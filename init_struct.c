/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 00:01:45 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/12 02:44:29 by dimitriyoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	assign_forks_philo(t_banquet *b)
{
	int	i;

	i = -1;
	while (++i < b->n_guests)
	{
		b->guests[i].left_fork = &b->forks[i];
		b->guests[i].right_fork = &b->forks[(i + 1) % b->n_guests];
	}
	return (0);
}

int	assign_struct(int ac, char **av, t_banquet *banquet)
{
	int	i;

	i = -1;
	banquet->n_guests = ft_atoi(av[1]);
	banquet->guests = malloc(sizeof(t_philo) * banquet->n_guests);
	banquet->forks = malloc(sizeof(pthread_mutex_t) * banquet->n_guests);
	if (!banquet->n_guests || !banquet->forks)
		return (-1);
	while (++i < banquet->n_guests)
	{
		if (pthread_mutex_init(banquet->forks + i, NULL) != 0)
			return (-2);
		banquet->guests[i].time_to_die = ft_atoi(av[2]);
		banquet->guests[i].time_to_eat = ft_atoi(av[3]);
		banquet->guests[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			banquet->guests[i].meals_limit = ft_atoi(av[5]);
		else
			banquet->guests[i].meals_limit = -1;
		banquet->guests[i].no = i + 1;
		assign_forks_philo(banquet);
	}
	return (1);
}

void	init_struct(t_banquet *banquet)
{
	banquet->guests = NULL;
	banquet->forks = NULL;
	banquet->n_guests = 0;
}
