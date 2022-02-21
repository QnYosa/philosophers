/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:54:10 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/22 00:21:38 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	*routine(void *b)
{
	t_philo	*phi;

	phi = (t_philo *)b;
	if (phi->no % 2 == 0)
		ft_usleep(phi->banquet, 50);
	while (!check_death(phi))
	{
		if (phi->meals_limit == 0)
			return (NULL);
		grab_fork(phi);
		if (phi->banquet->n_guests == 1)
		{
			return (NULL);
		}
		meal(phi);
		drop_fork(phi);
		if (sleeping(phi) || philo_is_full(phi))
			return (NULL);
		ft_usleep(phi->banquet, 1);
	}
	return (NULL);
}

int	isdeadboi(t_philo *phi)
{
	long	lastate;

	pthread_mutex_lock(&phi->banquet->eat);
	lastate = phi->last_meal;
	pthread_mutex_unlock(&phi->banquet->eat);
	if (init_time(phi->banquet) - lastate >= phi->time_to_die)
	{
		pthread_mutex_lock(&phi->banquet->check);
		if (!phi->banquet->end && !philo_is_full(phi))
			display_banquet(phi, "died", phi->banquet->t_start);
		phi->banquet->end = 1;
		pthread_mutex_unlock(&phi->banquet->check);
		return (1);
	}
	return (0);
}

void	single_monitor(t_banquet *b)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < b->n_guests)
		{
			if (isdeadboi(&b->guests[i]))
				return ;
		}
		ft_usleep(b, 1);
	}
}

int	create_threads(t_banquet *b)
{
	int				i;
	struct timeval	t;

	i = -1;
	gettimeofday(&t, NULL);
	b->t_start = (t.tv_usec / 1000) + (t.tv_sec * 1000);
	while (++i < b->n_guests)
	{
		if (pthread_create(&b->guests[i].philo, NULL, &routine, &b->guests[i]))
			return (-1);
	}
	single_monitor(b);
	i = -1;
	while (++i < b->n_guests)
	{
		if (pthread_join(b->guests[i].philo, NULL))
			return (-1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_banquet	banquet;

	if (parsing_maestro(ac, av) < 0)
		return (-1);
	if (init_struct(&banquet) < 0)
		return (-1);
	assign_struct(ac, av, &banquet);
	gettimeofday(&banquet.start_time, NULL);
	create_threads(&banquet);
	leaks_maestro(&banquet);
	return (0);
}
