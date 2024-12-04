/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:35:29 by anaouali          #+#    #+#             */
/*   Updated: 2024/02/09 12:41:31 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_strjoin(char *s1, char const s2)
{
	char	*tab;
	int		i;

	i = 0;
	if (!s1)
		s1 = ft_strdup("");
	tab = malloc(ft_strlen(s1) + 2);
	if (!tab)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i++] = s2;
	tab[i] = 0;
	free(s1);
	return (tab);
}

void	join(char c)
{
	static char	*str = NULL;

	if (c)
		str = ft_strjoin(str, c);
	else
	{
		ft_putstr("Your message : ");
		ft_putstr(str);
		write(1, "\n", 1);
		free(str);
		str = NULL;
	}
}

void	bit_decrypt(int sig, siginfo_t *struct_sa, void *t)
{
	static int	i = 0;
	static char	c = 0;

	(void)t;
	if (sig == SIGUSR1)
		c = (c << 1) | 0;
	else if (sig == SIGUSR2)
		c = (c << 1) | 1;
	if (i < 8)
		i++;
	if (i > 7)
	{
		join(c);
		i = 0;
		c = 0;
	}
	kill(struct_sa->si_pid, SIGUSR2);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = bit_decrypt;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_putstr("PREND LE TON PID... PREND LE !!!! : ");
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
