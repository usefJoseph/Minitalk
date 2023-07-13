/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychihab <ychihab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 06:46:36 by ychihab           #+#    #+#             */
/*   Updated: 2023/07/13 14:49:32 by ychihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar(n + '0');
}

void	func(int sig, siginfo_t *info, void *context)
{
	static int	a;
	static int	i;
	static int	client_pid;
	
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		i = 0;
		a = 0;
	}
	if (sig == SIGUSR1)
		a = (a << 1) | 1;
	else
		a = (a << 1);
	if (i == 7)
	{
		ft_putchar(a);
		a = 0;
		i = 0;
	}
	else
		i++;
}

int	main(void)
{
	ft_putnbr_fd(getpid(), 1);
	ft_putchar('\n');
	struct sigaction sa;

	sa.sa_sigaction = func;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1);
		return (0);
}

