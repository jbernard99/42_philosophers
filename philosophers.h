/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:43:32 by jbernard          #+#    #+#             */
/*   Updated: 2022/04/12 11:02:36 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define CRESET "\033[0m"
# define CBOLD "\033[1m"
# define CRED "\033[0;31m"
# define CGREEN "\033[0;32m"
# define CYELLOW "\033[0;33m"
# define CBLUE "\033[0;34m"
# define CPURPLE "\033[0;35m"
# define CCYAN "\033[0;36m"
# define CWHITE "\033[0;37m"

# define ERR "Error :"
# define ARG_NB_ERR "Wrong number of arguments.\n"
# define ARG_RANGE_ERR "An argument is invalid!"
# define THRD_ERR "Error during thread creations.\n"

# define PICK_L_FORK "picked up his left fork🍴"
# define PICK_R_FORK "picked up his right fork🍴"
# define EATING "is eating🍝"
# define SLEEPING "is sleeping😴"
# define THINKING "is thinking🤔"
# define DIED "DIED💀"

typedef struct s_data
{
	int				nb_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tm_eat;
	long long		start_time;
	int				stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	log_lock;
	pthread_mutex_t	last_ate;
}	t_data;

typedef struct s_philo
{
	t_data			*d;
	pthread_t		th;
	pthread_t		death_th;
	pthread_mutex_t	left_f;
	pthread_mutex_t	*right_f;
	int				id;
	int				stop;
	int				times_eaten;
	long long		last_t_ate;
}	t_philo;

typedef struct s_args
{
	int	nb_philo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	tm_eat;
}	t_args;

// validate_input.c //
int			validate_settings(t_args *args, int argc);
void		setup_settings(t_args *args, int argc, char *argv[]);

// routine.c //
void		*routine(void *arg);

// activity.c //
void		activity(t_philo *ph);

// init.c //
void		init_data(t_data *data, t_args *args);
t_philo		*init_philos(t_data *data);

// tools.c //
void		log_activity(t_philo *ph, char *str);
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_usleep(long long time_in_ms);
long long	get_time(void);

#endif
