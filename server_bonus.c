/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merilhan <mertilhanbv@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:29:03 by merilhan          #+#    #+#             */
/*   Updated: 2025/03/03 11:29:29 by merilhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

static void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	write(STDOUT_FILENO, &"0123456789"[n % 10], 1);
}

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	msg = 0;
	static int				count = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		msg |= (1 << (7 - count));
	count++;
	if (count == 8)
	{
		write(STDOUT_FILENO, &msg, 1);
		if (msg == '\0')
			kill(info->si_pid, SIGUSR2);
		msg = 0;
		count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putnbr(pid);
	write(STDOUT_FILENO, "\n", 1);
	while (1337)
		pause();
	return (0);
}
