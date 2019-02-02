/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adejbakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:05:44 by adejbakh          #+#    #+#             */
/*   Updated: 2019/02/02 20:19:00 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_synch_signal(int sig, siginfo_t *clt, void *t)
{
	sig_atomic_t clt_interrupt = 0;

	t = NULL;
	ft_info_manager(sig, clt);
	clt_interrupt = 1;
}

int main(void)
{
	struct sigaction clt_action;

	printf("%d\n", getpid());
	clt_action.sa_sigaction = ft_synch_signal;
	clt_action.sa_flags = SA_SIGINFO;
	sigaction (SIGUSR1, &clt_action, NULL);
	sigaction (SIGUSR2, &clt_action, NULL);
	while (1)
		;
	printf("done\n");
	return 0;
}
