/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:50:35 by adejbakh          #+#    #+#             */
/*   Updated: 2019/02/03 15:48:09 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"



t_cdata *get_cdata(void)
{
	static t_cdata *cdata;

	if (!cdata)
		cdata = (t_cdata *)ft_memalloc(sizeof(t_cdata));
	return (cdata);
}

void	send_char(t_cdata *cdata, char c)
{
	char i;

	i = 8;
	while (i--)
	{
		while (!cdata->flag.val)
		{
			kill(cdata->spid, c & 128 ? SIGUSR2 : SIGUSR1);
			usleep(5000);
		}
		cdata->flag.val = 0;
		c <<= 1;
	}
}

void	cli_sig_handler(int sig, siginfo_t *clt, void *t)
{
	t_cdata *cdata;

	cdata = get_cdata();	
	if (t)
		;
	if (cdata->spid != clt->si_pid)
		return ;
	if (sig == SIGUSR1)
	{
		cdata->flag.val <<= 1;
		cdata->flag.nbit += 1;
	}
	else if (sig == SIGUSR2)
	{
		cdata->flag.val = (cdata->flag.val << 1) + 1;
		cdata->flag.nbit += 1;
	}
}

void	send_text(t_cdata *cdata)
{
	while (cdata->text[cdata->sent])
		send_char(cdata, cdata->text[cdata->sent++]);
	send_char(cdata, 0);
}

int main(int argc, char **argv)
{
	struct sigaction clt_action;
	t_cdata *cdata;

	if (argc != 3 || !*argv[2])
		return (1);
	cdata = get_cdata();
	cdata->spid = ft_atoi(argv[1]);
	cdata->text = encoding(argv[2]);
	clt_action.sa_sigaction = cli_sig_handler;
	clt_action.sa_flags = SA_SIGINFO;
	sigaction (SIGUSR1, &clt_action, NULL);
	sigaction (SIGUSR2, &clt_action, NULL);
	while (!cdata->flag.val)
	{
		kill(cdata->spid, SIGUSR2);
		sleep(1);
	}
	cdata->flag.val = 0;
	send_text(cdata);
	ft_putendl("Envoyé");
	return (0);
}
