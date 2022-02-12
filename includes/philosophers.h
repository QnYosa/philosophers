/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:38:22 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/13 00:48:34 by dyoula           ###   ########.fr       */
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
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_limit;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					no;
	struct s_banquet	*banquet;
	long				last_meal;
}	t_philo;

typedef struct s_banquet
{
	t_philo			*guests;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	int				n_guests;
	long long		t_start;
}	t_banquet;

/*		PARSING.C		*/
int		parsing_maestro(int ac, char **av);

/*		PARSING_UTILS.C	*/
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);

/*		ERRORS.C		*/
int		parsing_errors(int n);

/*		INIT_STRUCT.C	*/
int		init_struct(t_banquet *banquet);
int		assign_struct(int ac, char **av, t_banquet *banquet);

/*		DISPLAY.C		*/
void	display_banquet(t_philo *phi, char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int nb, int fd);

/*		BANQUET.C		*/
int		grab_fork(t_philo *phi);
int		eat(t_philo *phi);
int		release_fork(t_philo *phi);
#endif