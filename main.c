/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:54:10 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/12 03:37:58 by dimitriyoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"


// void	*routines(t_banquet *b)
// {
// 	printf("salut\n");
// 	// grab fork

// 	// danger du deadlock faire attention a ce qu'ils n'aient pas tous leurs left fork
// 	// eat
// 	// sleep
// 	// think 
// 	return (NULL);
// }

// void *func3(void* param)
// {
//     pthread_mutex_lock(&mutex);
//     printf("Incrementing the shared variable...\n");
//     for (int i = 0; i < 10000; ++i) {
//         shared += 1;
//     }
//     pthread_mutex_unlock(&mutex);
//     return 0;
// }
// looks like a meal to me.
void	*routine(void *b)
{
	t_philo	*phi;

	phi = (t_philo *)b;
	while (1)
	{
		// printf("yo\n");
		grab_fork(phi);
	}
}

int	create_threads(t_banquet *b)
{
	int	i;

	i = -1;
	while (++i < b->n_guests)
	{
		if (pthread_create(&b->guests[i].philo, NULL, &routine, &b->guests[i]))
			return (-1);
	}
	i = -1;
	while (++i < b->n_guests)
	{
		if (pthread_join(b->guests[i].philo, NULL))
			return(-1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	// pthread_t	t1;
	// pthread_t	t2;
	t_banquet	banquet;

	if (parsing_maestro(ac, av) < 0)
		return (-1);
	init_struct(&banquet);
	assign_struct(ac, av, &banquet);
	create_threads(&banquet);
	// differencier les gauchers et les droitiers.
	// objectif faire la prise de fourchette
	printf("HELLO WORLD\n");
	return (0);
}
