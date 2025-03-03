/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merilhan <mertilhanbv@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:28:49 by merilhan          #+#    #+#             */
/*   Updated: 2025/03/03 11:33:55 by merilhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int	g_counter = 0;

static int	ft_atoi(char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * sign);
}

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_counter = 1;
	else if (sig == SIGUSR2)
	{
		write(STDOUT_FILENO, "message succesfuly delivered\n", 30);
		exit(0);
	}
}

void	transport_signal(int s_pid, char *msg)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	i = 0;
	while (msg[len++])
		;
	while (i <= len)
	{
		j = 7;
		while (j >= 0)
		{
			if ((msg[i] >> j) & 1)
				kill(s_pid, SIGUSR1);
			else
				kill(s_pid, SIGUSR2);
			usleep(30);
			while (g_counter == 0)
				pause();
			g_counter = 0;
			j--;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	s_pid;

	if (ac == 3)
	{
		s_pid = ft_atoi(av[1]);
		if (s_pid <= 0)
		{
			write(STDOUT_FILENO, "undefined pid \n", 16);
			exit(1);
		}
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		transport_signal(s_pid, av[2]);
		transport_signal(s_pid, "\n");
	}
	else
	{
		write(STDOUT_FILENO, "ERROR = Read The Manual\n", 25);
		return (1);
	}
	return (0);
}
