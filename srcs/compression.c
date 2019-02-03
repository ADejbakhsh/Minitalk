/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compression.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 21:43:21 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 16:31:31 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void
	encoding_fill_string(char *dst, char *src, int mode, int occ)
{
	char	c;
	size_t	i;

	i = 0;
	while ((c = *src))
	{
		if ((occ = count_occurence(src)) < 4 && mode)
		{
			*(dst++) = 1;
			i = count_only_one_occurence(src);
			*(dst++) = i;
			mode = 0;
		}
		else if (occ > 3)
		{
			*(dst++) = 2;
			*(dst++) = occ;
			src += occ - 1;
			mode = 1;
		}
		else if (i <= 1)
			mode = 1;
		*(dst++) = c;
		++src && --i;
	}
}

char
	*encoding(char *s)
{
	char	*new;

	if (!s)
		return (NULL);
	try_m(new = ft_strnew(ft_strlen(s) * 3));
	encoding_fill_string(new, s, 1, 0);
	return (new);
}

static int
	decoding_fill_string(char *dst, char *src)
{
	char	mode;
	char	occ;

	if (!dst || !src)
		return (1);
	while (*src)
	{
		mode = *(src++);
		occ = *(src++);
		if (mode == 1)
		{
			while (occ--)
				*(dst++) = *(src++);
		}
		else if (mode == 2)
		{
			while (occ--)
				*(dst++) = *src;
			++src;
		}
		else
			return (1);
	}
	return (0);
}

char
	*decoding(char *s)
{
	char	*new;

	if (!s)
		return (NULL);
	try_m(new = ft_strnew(encoded_text_length(s)));
	if (new && decoding_fill_string(new, s))
	{
		ft_strdel(&new);
		return (NULL);
	}
	return (new);
}
