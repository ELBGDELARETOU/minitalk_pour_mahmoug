/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:58:19 by hbaddrul          #+#    #+#             */
/*   Updated: 2024/02/09 12:15:39 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_gotit;

void	caught(int sig, siginfo_t *sa, void *t)
{
	(void)t;
	(void)sa;
	if (sig == SIGUSR2)
		g_gotit = 1;
}

void	a_to_b(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_gotit = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		bit--;
		while (g_gotit == 0)
			pause();
	}
}

void	send_str(int pid, char *str)
{
	int	i;
	int	str_len;

	str_len = ft_strlen(str);
	i = 0;
	while (i <= str_len)
	{
		a_to_b(pid, str[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	g_gotit = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = caught;
	sigaction(SIGUSR2, &sa, NULL);
	if (argc == 3)
	{
		ft_putstr("sending ...\n");
		send_str(ft_atoi(argv[1]), argv[2]);
		ft_putstr("sent\n");
		return (0);
	}
	else
	{
		ft_putstr("ERROR SYNTAX\n");
		ft_putstr("Format : ./client 'PID' 'Your message'\n");
	}
	return (0);
}
