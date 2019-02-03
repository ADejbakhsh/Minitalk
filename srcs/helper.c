/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 21:46:07 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 16:22:16 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	*try_m(void *ptr)
{
	if (!ptr)
	{
		ft_putendl("memory allocation error\n");
		exit(1);
	}
	return (ptr);
}


int		count_occurence(char *s)
{
	char	c;
	int		occ;

	occ = 0;
	c = s[occ++];
	while (s[occ] && c == s[occ])
		++occ;
	occ = (occ < 256 ? occ : 255);
	return (occ);
}

int		count_only_one_occurence(char *s)
{
	int		nb;
	int		occ;

	nb = 0;
	while (*s && nb < 256)
	{
		occ = count_occurence(s);
		if (occ > 3)
			return ((nb < 256 ? nb : 255));
		nb += occ;
		s += occ;
	}
	nb = (nb < 256 ? nb : 255);
	return (nb);
}

size_t	encoded_text_length(char *s)
{
	size_t	len;
	size_t	sublen;
	char	mode;
	size_t	i;

	len = 0;
	mode = 0;
	i = 0;
	while (s[i])
	{
		mode = s[i++];
		sublen = (unsigned char)s[i++];
		i += (mode == 2 ? 1 : sublen);
		len += sublen;
	}
	return (len);
}

t_sdata *get_sdata(void)
{
	static t_sdata *sdata;

	if (!sdata)
		sdata = (t_sdata *)ft_memalloc(sizeof(t_sdata));
	return (sdata);
}

t_connect *get_connection(t_sdata *sdata, int pid)
{
	t_connect *con;

	con = sdata->con;
	while (con && con->pid != pid)
		con = con->next;
	return (con);
}
