/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:32:23 by jbernard          #+#    #+#             */
/*   Updated: 2022/04/12 11:29:36 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*death(void *arg)
{
	t_philo	*ph;
	int		stop;

	ph = (t_philo *)arg;
	stop = 0;
	while (!stop)
	{
		pthread_mutex_lock(&ph->d->last_ate);
		if (get_time() - ph->last_t_ate > ph->d->tt_die)
		{
			pthread_mutex_unlock(&ph->d->last_ate);
			log_activity(ph, "died");
		}
		else
			pthread_mutex_unlock(&ph->d->last_ate);
		pthread_mutex_lock(&ph->d->stop_lock);
		stop = ph->stop + ph->d->stop;
		pthread_mutex_unlock(&ph->d->stop_lock);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*ph;
	int		stop;

	ph = (t_philo *)arg;
	ph->last_t_ate = ph->d->start_time;
	if (pthread_create(&ph->death_th, NULL, &death, ph))
		return (NULL);
	stop = 0;
	while (!stop)
	{
		activity(ph);
		pthread_mutex_lock(&ph->d->stop_lock);
		stop = ph->d->stop + ph->stop;
		pthread_mutex_unlock(&ph->d->stop_lock);
	}
	if (pthread_join(ph->death_th, NULL))
		return (NULL);
	return (NULL);
}
