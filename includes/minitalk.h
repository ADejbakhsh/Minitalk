/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adejbakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:17:51 by adejbakh          #+#    #+#             */
/*   Updated: 2019/02/02 19:51:31 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "../libft/includes/libft.h"
#define BUFSIZE 5

typedef struct	s_info
{
	char			*str;
	char			bit;
	int				pbit;
	int				pid;

	struct s_info	*next;
}					t_info;

void	ft_info_manager(int sig, siginfo_t *clt);

#endif

