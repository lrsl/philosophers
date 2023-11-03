/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:04:36 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/02 18:31:57 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_not_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	number;

	sign = 1;
	number = 0;
	if (*str == 0 || !str)
		return (0);
	while ((*str >= 8 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		number = number * 10 + *str - 48;
		str++;
	}
	return (number * sign);
}

int	args_check(char *arg, t_params *parameters)
{
	long	tmp;

	tmp = 0;
	if ((arg[0] == '\0') || (is_not_digit(arg)) || (ft_strlen(arg) > 11))
		error_manager(1);
	tmp = ft_atol(arg);
	if (tmp < 0 || tmp > 2147483647)
		error_parsing(7, parameters);
	return ((int)tmp);
}

t_params	*ft_parsing(int ac, char **av)
{
	t_params	*parameters;

	parameters = ft_calloc(1, sizeof(t_params));
	if (!parameters)
		error_malloc(parameters, 0);
	parameters->nb_philos = args_check(av[1], parameters);
	if (parameters->nb_philos > 250)
		error_parsing(81, parameters);
	parameters->time_death = args_check(av[2], parameters);
	if (parameters->time_death < 30)
		error_parsing(82, parameters);
	parameters->time_eat = args_check(av[3], parameters);
	if (parameters->time_eat < 30)
		error_parsing(83, parameters);
	parameters->time_sleep = args_check(av[4], parameters);
	if (parameters->time_sleep < 30)
		error_parsing(84, parameters);
	if (parameters->nb_philos % 2 == 1)
		parameters->time_think = ((parameters->time_eat) - \
		(parameters->time_sleep)) + 2;
	else
		parameters->time_think = 0;
	if (ac == 6)
		parameters->nb_max_meals = args_check(av[5], parameters);
	return (parameters);
}
