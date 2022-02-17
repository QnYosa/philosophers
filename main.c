/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:54:10 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/17 23:54:13 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	*routine(void *b)
{
	t_philo	*phi;

	phi = (t_philo *)b;
	phi->last_meal = phi->banquet->t_start;
	// display_banquet(phi, "tamere\n", phi->banquet->t_start);
	while (1)
	{
//		display_banquet(phi, "je suis bloque la", phi->banquet->t_start);
		if (is_dead(phi))
			return (NULL);
		if (grab_fork(phi, phi->banquet->t_start) < 0)
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
		usleep(2000);
	}
	i = 0;
	while (1)
	{
		if (check_death(&b->guests[i]) < 0)
			break ;
		i++;
		if (i == b->n_guests)
			i = 0;
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
	printf("HELLO WORLD\n");
	return (0);
}
