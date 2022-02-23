/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:54:10 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/23 08:55:05 by dimitriyoul      ###   ########.fr       */
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
			return (NULL);
		meal(phi);
		drop_fork(phi);
		sleeping(phi);
		if (philo_is_full(phi) < 0)
			return (NULL);
		ft_usleep(phi->banquet, 1);
	}
	return (NULL);
}

int	isdeadboi(t_philo *phi)
{
	long	difference;
	long	starved;

	pthread_mutex_lock(&phi->banquet->eat);
	starved = time_passed(phi->banquet->t_start);
	difference = time_passed(phi->last_meal);
	pthread_mutex_unlock(&phi->banquet->eat);
	if ((difference >= phi->time_to_die && phi->has_eaten_yet) \
		|| (starved >= phi->time_to_die && !phi->has_eaten_yet))
	{
		pthread_mutex_lock(&phi->banquet->lock);
		if (philo_is_full(phi) < 0)
		{
			pthread_mutex_unlock(&phi->banquet->lock);
			return (2);
		}
		else if (!phi->banquet->end)
			display_banquet(phi, "died", phi->banquet->t_start);
		pthread_mutex_lock(&phi->banquet->death);
		phi->banquet->end = 1;
		pthread_mutex_unlock(&phi->banquet->death);
		pthread_mutex_unlock(&phi->banquet->lock);
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
			if (isdeadboi(&b->guests[i]) > 0)
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
	// long		now;
	// long		then;
	// long		difference;

	if (parsing_maestro(ac, av) < 0)
		return (-1);
	if (init_struct(&banquet) < 0)
		return (-1);
	assign_struct(ac, av, &banquet);
	// now = init_time(&banquet);
	// usleep(500000);
	// then = init_time(&banquet);
	// difference = then - now;
	// printf("diff = %ld\n", difference);
	gettimeofday(&banquet.start_time, NULL);
	create_threads(&banquet);
	leaks_maestro(&banquet);
	return (0);
}
