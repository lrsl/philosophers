/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:19:59 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/02 17:53:54 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_philo_eats(t_params *parameters, t_philo *philo)
{
	pthread_mutex_lock(&parameters->forks[philo->left_fork]);
	philo_writting(parameters, philo->id_philo, FORK);
	pthread_mutex_lock(&parameters->forks[philo->right_fork]);
	philo_writting(parameters, philo->id_philo, FORK);
	pthread_mutex_lock(&parameters->check_time);
	philo->last_meal = get_time(parameters);
	pthread_mutex_unlock(&parameters->check_time);
	philo->meals++;
	pthread_mutex_lock(&parameters->check_all_ate);
	if (philo->meals == parameters->nb_max_meals)
		parameters->nb_philos_full++;
	pthread_mutex_unlock(&parameters->check_all_ate);
	philo_writting(parameters, philo->id_philo, EATS);
	blocked_time(parameters, parameters->time_eat);
	pthread_mutex_unlock(&parameters->forks[philo->right_fork]);
	pthread_mutex_unlock(&parameters->forks[philo->left_fork]);
}

void	ft_philo_sleeps(t_params *parameters, t_philo *philo)
{
	philo_writting(parameters, philo->id_philo, SLEEPS);
	blocked_time(parameters, parameters->time_sleep);
}

void	ft_philo_thinks(t_params *parameters, t_philo *philo)
{
	philo_writting(parameters, philo->id_philo, THINKS);
	if (parameters->time_think > 1)
		blocked_time(parameters, parameters->time_think);
}

void	philo_writting(t_params *parameters, int id_philo, char *str_to_print)
{
	pthread_mutex_lock(&parameters->check_death);
	if (parameters->alive_dead == ALIVE)
	{
		printf("%lld %d %s\n", get_time(parameters), id_philo, str_to_print);
	}
	pthread_mutex_unlock(&parameters->check_death);
}
