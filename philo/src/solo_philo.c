/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:18:54 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/02 15:36:57 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_is_alone(void *global_params)
{
	t_params	*parameters;
	t_philo		*philo;

	philo = (t_philo *)global_params;
	parameters = philo->parameters;
	pthread_mutex_lock(&parameters->forks[philo->left_fork]);
	philo_writting(parameters, philo->id_philo, FORK);
	blocked_time(parameters, parameters->time_death);
	philo_writting(parameters, philo->id_philo, DIED);
	pthread_mutex_unlock(&parameters->forks[philo->left_fork]);
	return (NULL);
}

void	philo_sitting_alone(t_params *parameters)
{
	if (pthread_mutex_init(&parameters->forks[0], NULL) != 0)
	{
		error_pthread(parameters, 2);
	}
	if (pthread_create(&parameters->philos[0].id_thread, NULL, \
	philo_is_alone, &parameters->philos[0]) != 0)
		error_pthread(parameters, 91);
	return ;
}
