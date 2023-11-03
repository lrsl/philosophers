/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:27:10 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/02 14:59:58 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_success_function(t_params *parameters)
{
	free(parameters->philos);
	free(parameters->forks);
	free(parameters);
	exit(EXIT_SUCCESS);
}

void	philos_leave_table(t_params *parameters)
{
	int	this_philo_id;

	this_philo_id = 0;
	while (this_philo_id < parameters->nb_philos)
	{
		if (pthread_join(parameters->philos[this_philo_id].id_thread, \
		NULL) != 0)
			error_pthread(parameters, 92);
		this_philo_id++;
	}
	this_philo_id = -1;
	while (++this_philo_id < parameters->nb_philos)
		if (pthread_mutex_destroy(&parameters->forks[this_philo_id]) != 0)
			error_pthread(parameters, 93);
	pthread_mutex_destroy(&parameters->check_death);
	pthread_mutex_destroy(&parameters->check_time);
	pthread_mutex_destroy(&parameters->check_all_ate);
}

int	main(int ac, char **av)
{
	t_params	*parameters;

	if (ac < 5 || ac > 6)
		return (write_error("Wrong arguments number, expected format:\n \
[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] \
([number_of_times_each_philosopher_must_eat])"));
	parameters = ft_parsing(ac, av);
	initialization(parameters);
	if (parameters->nb_philos == 1)
		philo_sitting_alone(parameters);
	else
		philos_dinning(parameters);
	philos_leave_table(parameters);
	free_success_function(parameters);
	return (0);
}
