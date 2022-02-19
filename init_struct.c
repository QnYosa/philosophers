/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 00:01:45 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/19 20:33:22 by dyoula           ###   ########.fr       */
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
		if (i == b->n_guests - 1)
			b->guests[i].right_fork = &b->forks[0];
		else
			b->guests[i].right_fork = &b->forks[i + 1];
	}
	return (0);
}

void	init_philo(t_banquet *banquet)
{
	int	i;

	i = -1;
	while (++i < banquet->n_guests)
	{
		banquet->guests[i].no = 0;
		banquet->guests[i].time_to_die = 0;
		banquet->guests[i].time_to_eat = 0;
		banquet->guests[i].time_to_sleep = 0;
		banquet->guests[i].banquet = NULL;
	}
}

int	init_struct(t_banquet *banquet)
{
	banquet->guests = NULL;
	banquet->forks = NULL;
	banquet->n_guests = 0;
	banquet->t_start = 0;
	banquet->end = 0;
	if (pthread_mutex_init(&banquet->mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&banquet->tlk_stick, NULL))
		return (-1);
	if (pthread_mutex_init(&banquet->display, NULL))
		return (-1);
	if (pthread_mutex_init(&banquet->death, NULL))
		return (-1);
	if (pthread_mutex_init(&banquet->eat, NULL))
		return (-1);
	if (pthread_mutex_init(&banquet->sleep, NULL))
		return (-1);
	if (pthread_mutex_init(&banquet->check, NULL))
		return (-1);
	return (1);
}

void	fill_philo(t_banquet *banquet, int ac, char **av, int i)
{
	banquet->guests[i].time_to_die = ft_atoi(av[2]);
	banquet->guests[i].time_to_eat = ft_atoi(av[3]);
	banquet->guests[i].time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		banquet->guests[i].meals_limit = ft_atoi(av[5]);
	else
		banquet->guests[i].meals_limit = -1;
	banquet->guests[i].no = i + 1;
	banquet->guests[i].banquet = banquet;
	assign_forks_philo(banquet);
}

int	assign_struct(int ac, char **av, t_banquet *banquet)
{
	int	i;

	i = -1;
	banquet->n_guests = ft_atoi(av[1]);
	banquet->guests = malloc(sizeof(t_philo) * banquet->n_guests);
	banquet->forks = malloc(sizeof(pthread_mutex_t) * banquet->n_guests);
	banquet->t_start = init_time();
	if (!banquet->n_guests || !banquet->forks)
		return (-1);
	init_philo(banquet);
	while (++i < banquet->n_guests)
	{
		if (pthread_mutex_init(banquet->forks + i, NULL) != 0)
			return (-2);
		fill_philo(banquet, ac, av, i);
	}
	return (1);
}
