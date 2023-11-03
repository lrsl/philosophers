/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:00:18 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/03 14:35:44 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philos_acting(void *data_philo)
{
	t_params	*parameters;
	t_philo		*philo;
	int			i;

	philo = (t_philo *)data_philo;
	parameters = philo->parameters;
	i = 0;
	if (!(philo->id_philo % 2))
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&parameters->check_death);
		if (parameters->alive_dead == DEAD)
		{
			pthread_mutex_unlock(&parameters->check_death);
			break ;
		}
		pthread_mutex_unlock(&parameters->check_death);
		ft_philo_eats(parameters, philo);
		ft_philo_sleeps(parameters, philo);
		usleep(200);
		ft_philo_thinks(parameters, philo);
		i++;
	}
	return (NULL);
}

int	starving(t_params *prm, t_philo *philos, int *i)
{
	pthread_mutex_lock(&prm->check_time);
	if ((get_time(prm) - philos[*i].last_meal) >= prm->time_death)
	{
		pthread_mutex_unlock(&prm->check_time);
		return (1);
	}
	pthread_mutex_unlock(&prm->check_time);
	return (2);
}

void	until_death_or_full(t_params *prm, t_philo *philos, \
int *i, bool *dead_or_alive)
{
	while (1)
	{
		pthread_mutex_lock(&prm->check_death);
		if (prm->alive_dead == DEAD)
		{
			pthread_mutex_unlock(&prm->check_death);
			break ;
		}
		pthread_mutex_unlock(&prm->check_death);
		if (starving(prm, philos, i) == 1)
			break ;
		usleep(1);
		pthread_mutex_lock(&prm->check_all_ate);
		if (prm->nb_philos_full == prm->nb_philos)
		{
			pthread_mutex_unlock(&prm->check_all_ate);
			*dead_or_alive = 1;
			break ;
		}
		pthread_mutex_unlock(&prm->check_all_ate);
		*i += 1;
		if (*i == prm->nb_philos - 1 || prm->nb_philos == 1)
			*i = 0;
	}
}

void	verif_status(t_params *parameters, t_philo *philos)
{
	int		i;
	bool	dead_or_alive;

	i = 0;
	dead_or_alive = 0;
	until_death_or_full(parameters, philos, &i, &dead_or_alive);
	if (dead_or_alive == 0)
		philo_writting(parameters, i + 1, DIED);
	else
	{
		usleep(100);
		pthread_mutex_lock(&parameters->check_death);
		printf(FULL, parameters->nb_max_meals);
		pthread_mutex_unlock(&parameters->check_death);
	}
	pthread_mutex_lock(&parameters->check_death);
	parameters->alive_dead = DEAD;
	pthread_mutex_unlock(&parameters->check_death);
	usleep(100);
}

void	philos_dinning(t_params *parameters)
{
	int	i;

	i = -1;
	while (++i < parameters->nb_philos)
		if (pthread_mutex_init(&parameters->forks[i], NULL) != 0)
			error_pthread(parameters, 2);
	i = -1;
	while (++i < parameters->nb_philos)
		if (pthread_create(&parameters->philos[i].id_thread, \
		NULL, philos_acting, &parameters->philos[i]) != 0)
			error_pthread(parameters, 91);
	while (1)
	{
		pthread_mutex_lock(&parameters->check_death);
		if (parameters->alive_dead == DEAD)
		{
			pthread_mutex_unlock(&parameters->check_death);
			break ;
		}
		pthread_mutex_unlock(&parameters->check_death);
		verif_status(parameters, parameters->philos);
		usleep(500);
	}
}
