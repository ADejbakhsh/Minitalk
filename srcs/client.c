/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:50:35 by adejbakh          #+#    #+#             */
/*   Updated: 2019/02/03 01:04:32 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_char
{
	int		nbit;
	char	val;
}				t_char;

typedef struct s_cdata
{
	t_char		flag;
	int			spid;
	char		*text;
}				t_cdata;

t_cdata *get_cdata(void)
{
	static t_cdata *cdata;

	if (!cdata)
		cdata = (t_cdata *)ft_memalloc(sizeof(t_cdata));
	return (cdata);
}

void	send_char(int pid, char c)
{
	char i;

	i = 8;
	while (i--)
	{
		printf("sig : %d\n", c & 128 ? SIGUSR2 : SIGUSR1);
		kill(pid, c & 128 ? SIGUSR2 : SIGUSR1);
		c <<= 1;
		usleep(5000);
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
 (void)cdata;
 // envoyer 8 a 8 avec un debut et une fin de mot
 // si pas de reponse 1
 //recommencer;
 // si oui les 8 suivant

}

int main(int argc, char **argv)
{
	struct sigaction clt_action;
	t_cdata *cdata;

	if (argc != 3)
		return (1);

	cdata = get_cdata();
	cdata->spid = ft_atoi(argv[1]);
	cdata->text = argv[2];
	clt_action.sa_sigaction = cli_sig_handler;
	clt_action.sa_flags = SA_SIGINFO;
	sigaction (SIGUSR1, &clt_action, NULL);
	sigaction (SIGUSR2, &clt_action, NULL);

	// ENVOIE start of string (2) et ATTEND ACK (6)
	while (!cdata->flag.val)
	{
		kill(cdata->spid, SIGUSR2);
		sleep(1);
	}
	cdata->flag.val = 0;
	send_text(cdata);
	send_char(cdata->spid, 4); //fin de message
	printf("youhou\n");

	return (0);
}
