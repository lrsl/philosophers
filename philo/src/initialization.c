/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:26:43 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/02 14:58:59 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_calloc(size_t nbelem, size_t size)
{
	unsigned char	*tab;
	unsigned int	i;

	if (size != 0 && nbelem > SIZE_MAX / size)
		return (NULL);
	tab = (unsigned char *)malloc(nbelem * size);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < nbelem * size)
	{
		tab[i] = '\0';
		i++;
	}	
	return ((void *)tab);
}

void	philos_init(t_params *parameters, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < parameters->nb_philos)
	{
		philos[i].id_philo = i + 1;
		philos[i].parameters = parameters;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % parameters->nb_philos;
		if (i == parameters->nb_philos - 1)
		{
			philos[i].right_fork = i;
			philos[i].left_fork = (i + 1) % parameters->nb_philos;
		}
		i++;
	}
}

void	initialization(t_params *parameters)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;

	parameters->time_start = get_time(parameters);
	philos = ft_calloc(parameters->nb_philos, sizeof(t_philo));
	if (!philos)
		error_malloc(parameters, 1);
	parameters->alive_dead = ALIVE;
	philos_init(parameters, philos);
	parameters->philos = philos;
	forks = ft_calloc(parameters->nb_philos, sizeof(pthread_mutex_t));
	if (!forks)
		error_malloc(parameters, 2);
	parameters->forks = forks;
	pthread_mutex_init(&parameters->check_death, NULL);
	pthread_mutex_init(&parameters->check_time, NULL);
	pthread_mutex_init(&parameters->check_all_ate, NULL);
}
