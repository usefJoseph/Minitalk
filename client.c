/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychihab <ychihab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 06:46:15 by ychihab           #+#    #+#             */
/*   Updated: 2023/07/13 14:35:27 by ychihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	ft_putchar(char c, int i)
{
	write(1, &c, 1);
}

void	ft_sendsignal(char c, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		i--;
	}
}

int	main(int argc, char *argv[])
{
	int	i;

	if (argc != 3)
		return (0);
	i = 0;
	while (argv[2][i])
	{
		ft_sendsignal(argv[2][i], atoi(argv[1]));
		i++;
	}
	return (0);
}
