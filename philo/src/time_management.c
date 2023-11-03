/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:40:49 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/02 16:44:20 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long int	get_time(t_params *parameters)
{
	struct timeval	time_struct;
	long long int	current_time;

	gettimeofday(&time_struct, NULL);
	current_time = (time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000) \
	- parameters->time_start;
	return (current_time);
}

void	blocked_time(t_params *parameters, long long sleep)
{
	long long int	start;

	start = get_time(parameters);
	while (1)
	{
		pthread_mutex_lock(&parameters->check_death);
		if (parameters->alive_dead == DEAD)
		{
			pthread_mutex_unlock(&parameters->check_death);
			break ;
		}
		pthread_mutex_unlock(&parameters->check_death);
		if (get_time(parameters) - start >= sleep)
			break ;
		usleep(1000);
	}
}
