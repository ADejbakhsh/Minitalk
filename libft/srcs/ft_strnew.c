/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adejbakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:00:13 by adejbakh          #+#    #+#             */
/*   Updated: 2018/11/13 17:19:41 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	a;
	char	*str;

	a = 0;
	if (!(str = (char*)malloc(sizeof(*str) * size + 1)))
		return (NULL);
	while (a <= size)
		str[a++] = 0;
	return (str);
}
