/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 21:46:07 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/02 21:58:07 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	merge(char **s1, char *s2)
{
	char *new;

	new = ft_strjoin(*s1, s2);
	if (!new)
		exit(1);
	ft_strdel(s1);
	*s1 = new;
}

int count_occurence(char *s)
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

int count_only_one_occurence(char *s)
{
	int		nb;
	int		occ;

	nb = 0;
	while (*s)
	{	
		occ = count_occurence(s);
		if (occ > 3)
			return (nb);
		nb += occ;
		s += occ;
	}
	return (nb);
}

size_t encoded_text_length(char *s)
{
	size_t	len;
	size_t	sublen;
	char	mode;

	len = 0;
	mode = 0;
	while (*s)
	{
		mode = *(s++);
		sublen = *(s++);
		s += (mode == 1 ? sublen : 1);
		len += sublen;	
	}
	return (len);
}
