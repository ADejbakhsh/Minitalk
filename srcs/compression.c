/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compression.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 21:43:21 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 16:06:29 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		encoding_fill_string(char *dst, char *src)
{
	int		mode;
	int		occ;
	char	c;
	size_t	i;

	if (!(mode = 1) || !dst || !src)
		return (1);
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
		++src;
		--i;
	}
	return (0);
}

char	*encoding(char *s)
{
	char	*new;

	if (!s)
		return (NULL);
	new = ft_strnew(ft_strlen(s) * 3);
	if (new && encoding_fill_string(new, s))
		ft_strdel(&new);
	return (new);
}

int		decoding_fill_string(char *dst, char *src)
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

char	*decoding(char *s)
{
	char	*new;

	if (!s)
		return (NULL);
	new = ft_strnew(encoded_text_length(s));
	decoding_fill_string(new, s);
	if (new && decoding_fill_string(new, s))
		ft_strdel(&new);
	return (new);
}
