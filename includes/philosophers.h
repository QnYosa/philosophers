/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:38:22 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/11 17:07:27 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_limit;
}	t_philo;

typedef struct s_banquet
{
	t_philo			*guests;
	pthread_mutex_t	*forks;
	int				n_guests;
}	t_banquet;

/*		PARSING.C		*/
int		parsing_maestro(int ac, char **av);

/*		PARSING_UTILS.C	*/
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

/*		ERRORS.C		*/
int		parsing_errors(int n);

/*		INIT_STRUCT.C	*/
void	init_struct(t_banquet *banquet);
int		assign_struct(int ac, char **av, t_banquet *banquet);

#endif