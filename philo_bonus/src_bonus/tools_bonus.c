/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:10:30 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/21 04:18:34 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_syntax(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!str_is_digit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time_;

	if (gettimeofday(&tv, NULL) == -1)
		return (__LONG_LONG_MAX__);
	time_ = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_);
}

void	sleep_job_time(long long sleep_time)
{
	long long	start;

	start = get_time();
	while (get_time() < start + sleep_time)
		usleep(100);
}

void	print_msg(t_philo_single_data *data, int msg, long long time)
{
	sem_wait(data->lp->dead);
	if (msg & DEAD)
	{
		printf("%lld philo %d is dead\n", get_time() - time, msg >> 8);
		return ;
	}
	else if (msg & EAT)
		printf("%lld philo %d is eating\n", get_time() - time, msg >> 8);
	else if (msg & SLEEP)
		printf("%lld philo %d is sleeping\n", get_time() - time, msg >> 8);
	else if (msg & THINK)
		printf("%lld philo %d is thinking\n", get_time() - time, msg >> 8);
	else if (msg & FORK)
		printf("%lld philo %d has taken a fork\n", get_time() - time, msg >> 8);
	sem_post(data->lp->dead);
}
