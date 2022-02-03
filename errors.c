/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:42:32 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/03 23:50:32 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	parsing_errors(int n)
{
	if (n == -1)
		printf("Wrong number of arguments\n");
	else if (n == -2)
		printf("Wrong caracters, only numbers allowed\n");
	return (n);
}
