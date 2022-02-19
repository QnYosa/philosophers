/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:54:10 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/19 21:00:37 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	*routine(void *b)
{
	t_philo	*phi;

	phi = (t_philo *)b;
	phi->last_meal = phi->banquet->t_start;
	if (phi->no % 2 == 0)
		usleep(100);
	while (!check_death(phi))
	{
		if (is_dead(phi) || check_death(phi))
			return (NULL);
		// printf("%ld et id = %d\n", phi->last_meal, phi->no);
		if (grab_fork(phi, phi->banquet->t_start) < 0)
			return (NULL);
		if (meal(phi) < 0)
		{
			drop_fork(phi, phi->banquet->t_start);
			return (NULL);
		}
		if (drop_fork(phi, phi->banquet->t_start))
			return (NULL);
		if (sleeping(phi) || philo_is_full(phi))
			return (NULL);
	}
	return (NULL);
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
		// usleep(1);
	}

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
	create_threads(&banquet);
	leaks_maestro(&banquet);
	printf("HELLO WORLD\n");
	return (0);
}
