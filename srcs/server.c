/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:43:27 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 16:09:55 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_sdata		*get_sdata(void)
{
	static t_sdata *sdata;

	if (!sdata)
		sdata = (t_sdata *)ft_memalloc(sizeof(t_sdata));
	return (sdata);
}

t_connect	*get_connection(t_sdata *sdata, int pid)
{
	t_connect *con;

	con = sdata->con;
	while (con && con->pid != pid)
		con = con->next;
	return (con);
}

void		handle_text(t_connect *con)
{
	char *tmp;

	if (con->len + 1 > con->maxlen)
	{
		con->maxlen *= 2;
		if (!(tmp = (char *)malloc(sizeof(char) * (con->maxlen + 1))))
			exit(1);
		ft_strcpy(tmp, con->text);
		ft_strdel(&con->text);
		con->text = tmp;
	}
	con->text[con->len++] = con->curchar.val;
	con->text[con->len] = 0;
}

void		handle_end_text(t_connect *con)
{
	char *decode;

	decode = decoding(con->text);
	ft_putstr("\e[1;32m");
	ft_putnbr(con->pid);
	ft_putstr(" > \e[0m");
	ft_putendl(decode);
	ft_strdel(&decode);
	//delete_con(pid);
}

void		handle_char(t_connect *con)
{
	if (con->curchar.val == 0)
		handle_end_text(con);
	else
		handle_text(con);
	ft_bzero((void *)&con->curchar, sizeof(t_char));
}

void		sig_dispatcher(t_sdata *sdata, int sig, int pid)
{
	t_connect *con;

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

void		ser_sig_handler(int sig, siginfo_t *clt, void *t)
{
	t_sdata *sdata;

	sdata = get_sdata();
	if (t)
		;
	if (clt->si_pid != 0 && (sig == SIGUSR1 || sig == SIGUSR2))
		sig_dispatcher(sdata, sig, clt->si_pid);
}

int			main(void)
{
	struct sigaction	clt_action;
	t_sdata				*sdata;

	sdata = get_sdata();
	ft_putstr("Server PID : \e[1;35m");
	ft_putnbr(getpid());
	ft_putendl("\e[0m\n");
	clt_action.sa_sigaction = ser_sig_handler;
	clt_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &clt_action, NULL);
	sigaction(SIGUSR2, &clt_action, NULL);
	while (1)
		;
	return (0);
}
