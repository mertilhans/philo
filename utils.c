/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merilhan <merilhan>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:57:16 by merilhan          #+#    #+#             */
/*   Updated: 2025/05/04 17:57:17 by merilhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

void	ft_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(250);
}

u_int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->sim->check_mutex);
	if (philo->sim->is_philo_dead)
	{
		pthread_mutex_unlock(&philo->sim->check_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->sim->time_mutex);
	printf("%llu	%d	%s", (get_time() - philo->sim->s_start), philo->id,
		status);
	pthread_mutex_unlock(&philo->sim->time_mutex);
	pthread_mutex_unlock(&philo->sim->check_mutex);
}
