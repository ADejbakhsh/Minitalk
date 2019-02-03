/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:25:57 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 16:48:26 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void
	*try_m(void *ptr)
{
	if (!ptr)
	{
		ft_putendl("memory allocation error\n");
		exit(1);
	}
	return (ptr);
}

void
	free_con(t_connect **con)
{
	t_connect *todel;

	todel = *con;
	*con = (*con)->next;
	if (todel->text)
		ft_strdel(&todel->text);
	todel->next = NULL;
	free(todel);
}

void
	delete_con(int pid)
{
	t_connect *con;

	con = get_sdata()->con;
	while (con && con->pid != pid)
		con = con->next;
	if (con)
		free_con(&con);
}

void
	free_cdata(t_cdata **cdata)
{
	if ((*cdata)->text)
		ft_strdel(&(*cdata)->text);
	free(*cdata);
}
