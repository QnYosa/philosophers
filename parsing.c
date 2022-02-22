/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:12:39 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/22 16:39:16 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	only_numbers(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]))
				return (-1);
	}
	return (0);
}

long	comp_max(char *s1, char *s2)
{
	long	i;

	i = 0;
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		while (s1[i] == s2[i])
		{
			if (i == (long)ft_strlen(s2))
				return (0);
			i++;
		}
	}
	return (1);
}

int	limit_int(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!comp_max(argv[i], "2147483648") || ft_strlen(argv[i]) > 10)
		{
			write(2, "Error\n", 6);
			return (0);
		}
	}
	return (1);
}

int	parsing_maestro(int ac, char **av)
{
	if (ac < 5)
		return (parsing_errors(-1));
	if (only_numbers(av) < 0)
		return (parsing_errors(-2));
	if (!ft_atoi(av[1]))
		return (-1);
	return (0);
}
