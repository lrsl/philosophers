/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:23:58 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/02 17:38:57 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <errno.h>
# include <stdbool.h>

/* DEFINE */
# define ALIVE 0
# define DEAD 1
# define FORK "has taken a fork"
# define EATS "is eating"
# define SLEEPS "is sleeping"
# define THINKS "is thinking"
# define DIED "\033[0;31mdied\033[0m"
# define FULL "\033[0;32mAll philosophers ate at least %d times\033[0m\n"

typedef struct s_philo	t_philo;
typedef struct s_params	t_params;

typedef struct s_philo
{
	pthread_t		id_thread;
	int				id_philo;
	int				left_fork;
	int				right_fork;
	int				meals;
	long long int	last_meal;
	bool			status;
	t_params		*parameters;
}	t_philo;

typedef struct s_params
{
	int				nb_philos;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				nb_max_meals;
	long long		time_start;
	int				nb_philos_full;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_death;
	pthread_mutex_t	check_time;
	pthread_mutex_t	check_all_ate;
	bool			alive_dead;
}	t_params;

/* dinner.c */
void				*philos_acting(void *data_philo);
int					starving(t_params *prm, t_philo *philos, int *i);
void				until_death_or_full(t_params *parameters, \
					t_philo *philos, int *i, bool *dead_or_alive);
void				verif_status(t_params *parameters, t_philo *philos);
void				philos_dinning(t_params *parameters);

/* errors.c */
int					write_error(char *str);
int					error_manager(int error);
void				error_parsing(int error, t_params *parameters);
void				error_malloc(t_params *parameters, int error_type);
void				error_pthread(t_params *parameters, int error_type);

/* initialization.c */
void				*ft_calloc(size_t nbelem, size_t size);
void				philos_init(t_params *parameters, t_philo *philos);
void				initialization(t_params *parameters);

/* main.c */
void				free_success_function(t_params *parameters);
void				philos_leave_table(t_params *parameters);

/* parsing.c */
int					ft_strlen(char *str);
int					is_not_digit(char *str);
long				ft_atol(const char *str);
int					args_check(char *arg, t_params *parameters);
t_params			*ft_parsing(int ac, char **av);

/* solo_philo.c */
void				*philo_is_alone(void *global_params);
void				philo_sitting_alone(t_params *parameters);

/* table.c */
void				ft_philo_eats(t_params *parameters, t_philo *philo);
void				ft_philo_sleeps(t_params *parameters, t_philo *philo);
void				ft_philo_thinks(t_params *parameters, t_philo *philo);
void				philo_writting(t_params *parameters, int id_philo, \
					char *str_to_print);

/* time_management.c */
long long int		get_time(t_params *parameters);
void				blocked_time(t_params *parameters, long long sleep);

#endif