/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:54:10 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/11 17:18:22 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	*routine(void)
{
	printf("salut\n");
	return (NULL);
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
	// phtread_create(&t1, NULL, &routine, NULL);
	// phtread_create(&t2, NULL, &routine, NULL);
	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
	printf("HELLO WORLD\n");
	return (0);
}
