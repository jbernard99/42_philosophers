/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:20:42 by jbernard          #+#    #+#             */
/*   Updated: 2022/04/11 12:34:47 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	give_forks(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->d->nb_philo)
	{
		if (ph->d->nb_philo == 1)
			ph[i].right_f = NULL;
		else
		{
			if (i == ph->d->nb_philo - 1)
				ph[i].right_f = &ph[0].left_f;
			else
				ph[i].right_f = &ph[i + 1].left_f;
		}
	}
}

t_philo	*init_philos(t_data *data)
{
	int	i;
	t_philo *ph;

	ph = malloc(sizeof(t_philo) * data->nb_philo);
	if (!ph)
		return (NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		ph[i].d = data;
		ph[i].id = i + 1;
		ph[i].stop = 0;
		ph[i].last_t_ate = 0;
		ph[i].times_eaten = 0;
		ph[i].right_f = NULL;
		ph[i].death_th = NULL;
		ph[i].th = NULL;
		pthread_mutex_init(&ph[i].left_f, NULL);
	}
	give_forks(ph);
	return (ph);
}

void	init_data(t_data *data, t_args *args)
{
	data->nb_philo = args->nb_philo;
	data->tt_die = args->tt_die;
	data->tt_eat = args->tt_eat;
	data->tt_sleep = args->tt_sleep;
	data->tm_eat = args->tm_eat;
	data->stop = 0;
	data->start_time = get_time();
	pthread_mutex_init(&data->stop_lock, NULL);
	pthread_mutex_init(&data->log_lock, NULL);
	pthread_mutex_init(&data->last_ate, NULL);
}