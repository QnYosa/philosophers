/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 03:10:22 by dimitriyoul       #+#    #+#             */
/*   Updated: 2022/02/23 20:30:49 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	display_banquet(t_philo *phi, char *str, long start)
{
	pthread_mutex_lock(&phi->banquet->tlk_stick);
	printf("%ld %d %s\n", time_passed(start), phi->no, str);
	pthread_mutex_unlock(&phi->banquet->tlk_stick);

}

void	ft_putstr_fd(char *str, int fd)
{
	int	a;

	a = ft_strlen(str);
	write(fd, str, a);
	a++;
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb < 0)
	{
		ft_putchar('-', fd);
		nb *= -1;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar(nb % 10 + 48, fd);
}
