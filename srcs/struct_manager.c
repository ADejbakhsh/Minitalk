/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adejbakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:50:49 by adejbakh          #+#    #+#             */
/*   Updated: 2019/02/02 19:55:43 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_info		*ft_static_struct(void)
{
	static t_info	*p;

	if (!(p))
		return NULL;
	return (p);
}

int		ft_sig(int sig)
{
	if (sig == 30 || sig == 10 ||sig == 16)
		return (0);
	if (sig == 31 || sig == 12 ||sig == 17)
		return (1);
	return (-1);
}

t_info		*ft_init_struct(int sig, siginfo_t *clt, t_info *p)
{
	if (p)
		return (p);
	if (!(p = malloc(sizeof(*p))))
		return (NULL);
	if (!(p->str = ft_strnew(BUFSIZE)))
		return (NULL);
	p->bit = ft_sig(sig) << 0;
	p->pbit = 1;
	p->pid =  clt->si_pid;
	p->next = NULL;
	return (p);
}

void	ft_existing(t_info *s, int sig)
{
	s->pbit++;
	s->bit = ft_sig(sig) << 1;
	if (s->pbit % 8 == 0)
	{
		if (s->pbit == BUFSIZE * (s->pbit / BUFSIZE))
		{
			printf("%s\n", s->str);
			exit(2);
			ft_realloc(s->str, BUFSIZE);
		}
		s->str[s->bit / 8] = s->bit;
	}
}

void	ft_info_manager(int sig, siginfo_t *clt)
{
	t_info			*s;

	s = ft_init_struct(sig, clt, ft_static_struct());
	while (s)
	{
		if (s->pid == clt->si_pid)
		{
			ft_existing(s, sig);
			return ;
		}
		s = s->next;
	}
	s = ft_init_struct(sig, clt, s);
}
