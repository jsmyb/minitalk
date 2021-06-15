/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoghomo <lsoghomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:58:57 by lsoghomo          #+#    #+#             */
/*   Updated: 2021/06/15 21:01:36 by lsoghomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	dec_conversion(char asci, int power, int pid)
{
	if (power > 0)
		dec_conversion(asci / 2, power - 1, pid);
	if ((asci % 2) == 1)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_putstr("Signal error\n");
			exit(0);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_putstr("Signal error!\n");
			exit(0);
		}
	}
	usleep(100);
}

int	send_msg(int server_pid, char *msg)
{
	int		i;

	i = 0;
	while (msg[i] != '\0')
	{
		dec_conversion(msg[i], 7, server_pid);
		i++;
	}
	return (0);
}

void	handler(int signum, siginfo_t *siginfo, void *unused)
{
	(void)unused;
	(void)siginfo;
	(void)signum;
	ft_putstr("Signal received\n");
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if ((sigaction(SIGUSR2, &sa, 0)) == -1)
		error("Sigaction error\n");
	if (argc == 3)
		send_msg(atoi(argv[1]), argv[2]);
	else
		error("Sigaction error\n");
	while (1)
		pause();
	return (0);
}
