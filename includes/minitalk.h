/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:00:17 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 00:19:10 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

# include "libft.h"

# define MTBUFFSIZE 256

typedef struct	s_info
{
	char			*str;
	char			bit;
	int				pbit;
	int				pid;

	struct s_info	*next;
}					t_info;

int		encoding_fill_string(char *dst, char *src);
char	*encoding(char *s);
int		decoding_fill_string(char *dst, char *src);
char	*decoding(char *s);
int		count_occurence(char *s);
int		count_only_one_occurence(char *s);
size_t	encoded_text_length(char *s);
void	send_char(int pid, char c);

void	ft_info_manager(int sig, siginfo_t *clt);

#endif

