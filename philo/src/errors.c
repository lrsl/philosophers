/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:26:52 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/02 14:57:29 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (write_error("Issue with at least one argument."));
	if (error == 2)
		return (write_error("Issue whith the mutex intialization."));
	if (error == 3)
		return (write_error("Malloc failed."));
	if (error == 4)
		return (write_error("Params structure initialization failed."));
	if (error == 5)
		return (write_error("Philo structure table initialization failed."));
	if (error == 6)
		return (write_error("Fork mutex table initialization failed."));
	if (error == 9)
		return (write_error("Thread failed."));
	if (error == 91)
		return (write_error("Creating thread failed."));
	if (error == 92)
		return (write_error("Joining thread failed."));
	if (error == 93)
		return (write_error("Destroying mutex failed."));
	return (1);
}

void	error_parsing(int error, t_params *parameters)
{
	if (error == 7)
		write_error("Parameters must be positive ints.");
	if (error == 81)
		write_error("Too many philosophers.");
	if (error == 82)
		write_error("Time before death is too short.");
	if (error == 83)
		write_error("Not enough time to eat.");
	if (error == 84)
		write_error("Not enough time to sleep.");
	free(parameters);
	exit(EXIT_FAILURE);
}

void	error_malloc(t_params *parameters, int error_type)
{
	int	level;

	level = error_type;
	error_manager(3);
	while (level > 0)
	{
		if (level == 1)
			free(parameters);
		if (level == 2)
			free(parameters->philos);
		level--;
	}
	if (error_type == 0)
		error_manager(4);
	else if (error_type == 1)
		error_manager(5);
	else if (error_type == 2)
		error_manager(6);
	exit(EXIT_FAILURE);
}

void	error_pthread(t_params *parameters, int error_type)
{
	free(parameters->philos);
	free(parameters->forks);
	free(parameters);
	error_manager(9);
	error_manager(error_type);
	exit(EXIT_FAILURE);
}
