/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:38:22 by dyoula            #+#    #+#             */
/*   Updated: 2022/02/24 03:31:17 by dyoula           ###   ########.fr       */
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
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_to_think;
	int					meals_limit;
	int					has_eaten_yet;
	long				starved;
	long				difference;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		block;
	int					no;
	struct s_banquet	*banquet;
	long				last_meal;
}	t_philo;

typedef struct s_banquet
{
	t_philo			*guests;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	pthread_mutex_t	death;
	pthread_mutex_t	eat;
	pthread_mutex_t	display;
	pthread_mutex_t	sleep;
	pthread_mutex_t	tlk_stick;
	pthread_mutex_t	check;
	pthread_mutex_t	lock;
	int				n_guests;
	long long		t_start;
	int				end;
	struct timeval	start_time;
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
void	display_banquet(t_philo *phi, char *str, long start);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int nb, int fd);

/*		BANQUET.C		*/
int		sleeping(t_philo *phi);
int		meal(t_philo *phi);
int		grab_fork(t_philo *phi);
int		drop_fork(t_philo *phi);

/*		TIME.C			*/
long	time_passed(long last);
long	last_meal_update(void);
int		ft_usleep_eat(t_philo *phi);
void	ft_usleep(t_banquet *b, long time);
long	init_time(t_banquet *b);

/*		CHECK_DEATH.C	*/
int		check_death(t_philo *phi);
int		philo_is_full(t_philo *phi);
int		is_dead(t_philo *phi);
long	current_time(void);

/*		LEAKS.C			*/
int		leaks_maestro(t_banquet *banquet);

/*		NORM.C			*/
int		norm_isdeadboi(t_philo *phi);

#endif