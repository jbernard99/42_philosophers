/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:49:52 by jbernard          #+#    #+#             */
/*   Updated: 2022/04/12 11:30:47 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_activity(t_philo *ph, char *str)
{
	long long	elapsed_time;

	pthread_mutex_lock(&ph->d->stop_lock);
	if (ph->d->stop == 1)
	{
		pthread_mutex_unlock(&ph->d->stop_lock);
		return ;
	}
	if (!ft_strcmp(str, "died"))
		ph->d->stop = 1;
	pthread_mutex_unlock(&ph->d->stop_lock);
	elapsed_time = get_time() - ph->d->start_time;
	pthread_mutex_lock(&ph->d->log_lock);
	if (!ph->d->stop)
		printf("%lldms : Philosopher #%d %s.\n", elapsed_time, ph->id, str);
	else
		printf("%lldms : Philosopher #%d " DIED ".\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&ph->d->log_lock);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_atoi(const char *str)
{
	long			total;
	int				i;
	int				sign;

	total = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = total * 10 + (str[i] - '0');
		i++;
		if (total * sign > 2147483647)
			return (0);
		if (total * sign < -2147483648)
			return (0);
	}
	return (sign * total);
}

void	ft_usleep(long long time_in_ms)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(1);
}

long long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
