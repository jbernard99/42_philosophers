/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:08:15 by jbernard          #+#    #+#             */
/*   Updated: 2022/04/07 10:10:01 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_settings(t_args *args, int argc)
{
	if (args->nb_philo < 1 || args->nb_philo > 200)
		return (0);
	if (args->tt_die < 60)
		return (0);
	if (args->tt_eat < 60)
		return (0);
	if (args->tt_sleep < 60)
		return (0);
	if (argc == 5)
	{
		if (args->tm_eat < 1)
			return (0);
	}
	return (1);
}

void	setup_settings(t_args *args, int argc, char *argv[])
{
	args->nb_philo = ft_atoi(argv[0]);
	args->tt_die = ft_atoi(argv[1]);
	args->tt_eat = ft_atoi(argv[2]);
	args->tt_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		args->tm_eat = ft_atoi(argv[4]);
	else
		args->tm_eat = 0;
}
