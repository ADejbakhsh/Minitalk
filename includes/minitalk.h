/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:00:17 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/03 16:21:05 by hben-yah         ###   ########.fr       */
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

typedef struct s_char
{
	int		nbit;
	char	val;
}				t_char;

typedef struct s_cdata
{
	t_char		flag;
	int			spid;

	char		*text;
	//size_t		len;
	size_t		sent;
}				t_cdata;

typedef struct s_connect
{
	int					pid;
	char				*text;
	size_t				len;
	size_t				maxlen;

	char				word[8];
	size_t				wlen;
	t_char				curchar;
	struct s_connect	*next;
}				t_connect;

typedef struct s_sdata
{
	t_connect	*con;
}				t_sdata;

char		*encoding(char *s);
char		*decoding(char *s);
int			count_occurence(char *s);
int			count_only_one_occurence(char *s);
size_t		encoded_text_length(char *s);
void		send_char(t_cdata *cdata, char c);
t_sdata		*get_sdata(void);
t_connect	*get_connection(t_sdata *sdata, int pid);
void		handle_char(t_connect *con);
void		*try_m(void *ptr);

#endif
