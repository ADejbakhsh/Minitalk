/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:43:27 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 00:59:48 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_char
{
	int		nbit;
	char	val;
}				t_char;

typedef struct s_connect
{
	int					pid;
	char				*text;
	size_t				len;
	size_t				maxlen;

	char				word[8];
	size_t				wlen;
	t_char				curchar;
	struct s_connect	*next;
}				t_connect;

typedef struct s_sdata
{
	t_connect	*con;
}				t_sdata;

t_sdata *get_sdata(void)
{
	static t_sdata *sdata;

	if (!sdata)
		sdata = (t_sdata *)ft_memalloc(sizeof(t_sdata));
	return (sdata);
}

void	send_char(int pid, char c)
{
	char i;

	i = 8;
	while (i--)
	{
		kill(pid, c & 127 ? SIGUSR2 : SIGUSR1);
		c <<= 1;
		usleep(5000);
	}
}

t_connect *get_connection(t_sdata *sdata, int pid)
{
	t_connect *con;

	con = sdata->con;
	while (con && con->pid != pid)
		con = con->next;
	return (con);
}

void	handle_text(t_connect *con)
{
	con->word[con->wlen++] = con->curchar.val;
	ft_bzero((void *)&con->curchar, sizeof(t_char));
}

void	handle_beg_word(t_connect *con)
{
	con->wlen = 0;
	send_char(con->pid, 6);
}

void	handle_end_word(t_connect *con)
{
	char *tmp;

	if (con->wlen < 8)
		send_char(con->pid, 21);
	else
	{
		if (con->len + con->wlen > con->maxlen)
		{
			con->maxlen *= 2;
			if(!(tmp = ft_strnew(con->maxlen)))
				exit(1);
			ft_strcpy(tmp, con->text);
			ft_strdel(&con->text);
			con->text = tmp;
		}
		ft_strncpy(con->text, con->word, con->wlen);
		send_char(con->pid, 6);
	}
	con->wlen = 0;
}

void	handle_end_text(t_connect *con)
{
	int pid;

	pid = con->pid;
	con = NULL;
	//delete_con(pid);
}

void	handle_char(t_connect *con)
{
	if (con->curchar.val == 2)
		handle_beg_word(con);
	else if (con->curchar.val == 3)
		handle_end_word(con);
	else if (con->curchar.val == 4)
		handle_end_text(con);
	else
		handle_text(con);
}

void	sig_dispatcher(t_sdata *sdata, int sig, int pid)
{
	t_connect *con;

	con = get_connection(sdata, pid);
	
	if (!con)
	{
		if(!(con = (t_connect *)ft_memalloc(sizeof(t_connect)))
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
	}
}

void	ser_sig_handler(int sig, siginfo_t *clt, void *t)
{
	t_sdata *sdata;

	sdata = get_sdata();
	if (t)
		;
	if (sig == SIGUSR1 || sig == SIGUSR2)
		sig_dispatcher(sdata, sig, clt->si_pid);
}



int main(void)
{
	struct sigaction clt_action;
	t_sdata *sdata;

	sdata = get_sdata();

	ft_putnbr(getpid());
	ft_putchar('\n');
	clt_action.sa_sigaction = ser_sig_handler;
	clt_action.sa_flags = SA_SIGINFO;
	sigaction (SIGUSR1, &clt_action, NULL);
	sigaction (SIGUSR2, &clt_action, NULL);
	while (1)
		;
	return (0);
}
