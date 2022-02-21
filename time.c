/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:13:27 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/21 23:48:36 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

long	time_passed(long last)
{
	struct timeval	time;
	long			now;

	gettimeofday(&time, NULL);
	now = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (now - last);
}

long	last_meal_update(void)
{
	struct timeval	time;
	long			now;

	gettimeofday(&time, NULL);
	now = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (now);
}

int	ft_usleep_eat(t_philo *phi)
{
	int	i;
	int	sleep;

	i = -1;
	sleep = phi->time_to_sleep * 100;
	while (i++ < 10)
		usleep(sleep);
	return (1);
}

void	ft_usleep(t_banquet *b, long time)
{
	long	now;

	now = init_time(b);
	while (1)
	{
		if (init_time(b) - now >= time)
			return ;
		usleep(51);
	}
}

long	init_time(t_banquet *b)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - b->start_time.tv_sec) * 1000 + \
	(now.tv_usec - b->start_time.tv_usec) / 1000);
}
