/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:54:10 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/19 00:17:45 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	sleeping(t_philo *phi)
{
	if (is_dead(phi))
		return (-1);
	display_banquet(phi, "is sleeping", phi->banquet->t_start);
	ft_usleep(phi->time_to_sleep);
	display_banquet(phi, "is_thinking", phi->banquet->t_start);
	return (0);
}

void	*routine(void *b)
{
	t_philo	*phi;

	phi = (t_philo *)b;
	phi->last_meal = phi->banquet->t_start;
	while (!check_death(phi))
	{
		if (phi->no % 2 == 0)
			usleep(25);
		if (is_dead(phi))
			return (NULL);
		if (grab_fork(phi, phi->banquet->t_start) < 0)
			return (NULL);
		if (meal(phi) < 0)
		{
			drop_fork(phi, phi->banquet->t_start);
			return (NULL);
		}
		if (drop_fork(phi, phi->banquet->t_start))
			return (NULL);
		if (sleeping(phi))
			return (NULL);
		if (philo_is_full(phi))
			return (NULL);
		// display_banquet(phi, "je suis bloque la", phi->banquet->t_start);
		// if ()
		// {
		// 	display_banquet(phi, "on a un mort\n", phi->banquet->t_start);
		// 	return (NULL);
		// }
		// if (meal(phi) < 0)
		// {
		// 	drop_fork(phi, phi->banquet->t_start);
		// 	return (NULL);
		// }
		// pthread_mutex_lock(&phi->banquet->death);
		// if (grab_fork(phi, phi->banquet->t_start) < 0)
		// 	return (NULL);
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
		// usleep(2000);
	}
	// i = 0;
	// while (1)
	// {
	// 	if (check_death(&b->guests[i]) == 1)
	// 		break ;
	// 	i++;
	// 	if (i == b->n_guests)
	// 		i = 0;
	// }
	// display_banquet()
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
