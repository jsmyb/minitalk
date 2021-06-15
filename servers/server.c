/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoghomo <lsoghomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:58:47 by lsoghomo          #+#    #+#             */
/*   Updated: 2021/06/15 21:01:12 by lsoghomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	sigtostr(int bin)
{
	char	c;
	int		i;

	i = 0;
	c = '\0';
	c += (bin << i++);
	if (i > 7)
	{
		if (c == '\0')
			ft_putchar('\n');
		else
			ft_putchar(c);
		c = 0;
		i = 0;
	}
}

void	handler(int sig_num, siginfo_t *siginfo, void *unused)
{
	static int	asci = 0;
	static int	power = 0;

	(void)unused;
	if (sig_num == SIGUSR1)
		asci += 1 << (7 - power);
	power += 1;
	if (power == 8)
	{
		ft_putchar(asci);
		power = 0;
		asci = 0;
		if (kill(siginfo->si_pid, SIGUSR2) == -1)
			error("Signal error\n");
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
		error("Error arguments\n");
	write(1, "Server launched!\nPID: ", 21);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if ((sigaction(SIGUSR1, &sa, 0)) == -1)
		error("Sigaction error\n");
	if ((sigaction(SIGUSR2, &sa, 0)) == -1)
		error("Sigaction error\n");
	while (1)
		pause();
	return (0);
}
