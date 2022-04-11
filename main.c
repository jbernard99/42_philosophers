/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:59:59 by jbernard          #+#    #+#             */
/*   Updated: 2022/04/11 12:47:27 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_dinner(t_philo *ph)
{
	int	i;

	i = -1;
	ph[0].d->start_time = get_time();
	while (++i < ph->d->nb_philo)
	{
		if (pthread_create(&ph[i].th, NULL, routine, &ph[i]))
			return (0);
	}
	i = -1;
	while (++i < ph->d->nb_philo)
	{
		if(pthread_join(ph[i].th, NULL))
			return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_args		args;
	t_data		*data;
	t_philo		*ph;

	data = malloc(sizeof(t_data));
	argv++;
	if (--argc < 4 || argc > 5)
		return (printf("Wrong number of arguments."));
	setup_settings(&args, argc, argv);
	if (!validate_settings(&args, argc))
		return (printf("An argument is invalid! (1st:[1:200]; 2nd,3rd,4fth >= 60; 5th >= 1)"));
	init_data(data, &args);
	ph = init_philos(data);
	write(1, "Before Dinner OK\n", 17);
	if (!start_dinner(ph))
		return (printf("Error during thread creations."));
	return (0);
}