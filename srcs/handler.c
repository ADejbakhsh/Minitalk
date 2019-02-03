/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:04:04 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 16:41:04 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void
	handle_text(t_connect *con)
{
	char *tmp;

	if (con->len + 1 > con->maxlen)
	{
		con->maxlen *= 2;
		try_m(tmp = (char *)malloc(sizeof(char) * (con->maxlen + 1)));
		ft_strcpy(tmp, con->text);
		ft_strdel(&con->text);
		con->text = tmp;
	}
	con->text[con->len++] = con->curchar.val;
	con->text[con->len] = 0;
}

static void
	handle_end_text(t_connect *con)
{
	char *decode;

	decode = decoding(con->text);
	ft_putstr("\e[1;32m");
	ft_putnbr(con->pid);
	ft_putstr(" > \e[0m");
	if (!decode)
		ft_putendl("Message compressé invalide");
	else
		ft_putendl(decode);
	ft_strdel(&decode);
	delete_con(con->pid);
}

void
	handle_char(t_connect *con)
{
	if (con->curchar.val == 0)
		handle_end_text(con);
	else
		handle_text(con);
	ft_bzero((void *)&con->curchar, sizeof(t_char));
}
