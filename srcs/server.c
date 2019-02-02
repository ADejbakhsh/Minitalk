/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adejbakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:05:44 by adejbakh          #+#    #+#             */
/*   Updated: 2019/02/02 15:55:05 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


void	synch_signal(int sig, siginfo_t *clt, void *t)
{
	sig_atomic_t clt_interrupt = 0;

	printf("%d\n", sig);
	printf("%d\n", clt->si_pid);
	clt_interrupt = 1;
}

int main(void)
{
	struct sigaction clt_action;

	printf("%d\n", getpid());
	clt_action.sa_sigaction = synch_signal;
	clt_action.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction (SIGUSR1, &clt_action, NULL);
		sigaction (SIGUSR2, &clt_action, NULL);
	}
	printf("done\n");
	return 0;
}
