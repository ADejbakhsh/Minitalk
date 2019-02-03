/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:43:27 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 16:07:02 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void
	sig_dispatcher(t_sdata *sdata, int sig, int pid)
{
	t_connect	*con;

	con = get_connection(sdata, pid);
	if (!con)
	{
		if (!(con = (t_connect *)ft_memalloc(sizeof(t_connect)))
			|| !(con->text = ft_strnew(MTBUFFSIZE)))
			exit(1);
		con->maxlen = MTBUFFSIZE;
		con->next = sdata->con;
		con->pid = pid;
		sdata->con = con;
		kill(con->pid, SIGUSR2);
	}
	else
	{
		con->curchar.val = (con->curchar.val << 1) + (sig == SIGUSR2);
		con->curchar.nbit += 1;
		if (con->curchar.nbit >= 8)
			handle_char(con);
		kill(con->pid, SIGUSR2);
	}
}

static void
	ser_sig_handler(int sig, siginfo_t *clt, void *t)
{
	t_sdata		*sdata;

	sdata = get_sdata();
	if (t)
		;
	if (clt->si_pid != 0 && (sig == SIGUSR1 || sig == SIGUSR2))
		sig_dispatcher(sdata, sig, clt->si_pid);
}

int
	main(void)
{
	struct sigaction	clt_action;
	t_sdata				*sdata;

	sdata = get_sdata();
	ft_putstr("Server PID : \e[1;35m");
	ft_putnbr(getpid());
	ft_putendl("\e[0m\n");
	clt_action.sa_sigaction = ser_sig_handler;
	clt_action.sa_flags = SA_SIGINFO;
	sigaction (SIGUSR1, &clt_action, NULL);
	sigaction (SIGUSR2, &clt_action, NULL);
	while (1)
		;
	return (0);
}
