/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:02:49 by jbernard          #+#    #+#             */
/*   Updated: 2022/04/12 10:57:46 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	even_ph(t_philo *ph)
{
	pthread_mutex_lock(ph->right_f);
	log_activity(ph, PICK_R_FORK);
	if (ph->d->nb_philo == 1)
	{
		pthread_mutex_unlock(ph->right_f);
		ft_usleep(ph->d->tt_die);
		return ;
	}
	pthread_mutex_lock(&ph->left_f);
	log_activity(ph, PICK_L_FORK);
	log_activity(ph, EATING);
	ph->times_eaten++;
	ph->last_t_ate = get_time();
	ft_usleep(ph->d->tt_eat);
	pthread_mutex_unlock(ph->right_f);
	pthread_mutex_unlock(&ph->left_f);
}

void	odd_ph(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_f);
	log_activity(ph, PICK_L_FORK);
	if (ph->d->nb_philo == 1)
	{
		pthread_mutex_unlock(&ph->left_f);
		ft_usleep(ph->d->tt_die);
		return ;
	}
	pthread_mutex_lock(ph->right_f);
	log_activity(ph, PICK_R_FORK);
	log_activity(ph, EATING);
	ph->times_eaten++;
	ph->last_t_ate = get_time();
	ft_usleep(ph->d->tt_eat);
	pthread_mutex_unlock(&ph->left_f);
	pthread_mutex_unlock(ph->right_f);
}

void	activity(t_philo *ph)
{
	if (ph->id % 2 == 0)
		even_ph(ph);
	else
		odd_ph(ph);
	if (ph->d->tm_eat && ph->times_eaten == ph->d->tm_eat)
	{
		pthread_mutex_lock(&ph->d->stop_lock);
		ph->stop = 1;
		pthread_mutex_unlock(&ph->d->stop_lock);
		return ;
	}
	log_activity(ph, SLEEPING);
	ft_usleep(ph->d->tt_sleep);
	log_activity(ph, THINKING);
}
