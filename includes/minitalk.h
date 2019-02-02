/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:00:17 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/02 22:02:24 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdio.h>
# include "libft.h"


int		encoding_fill_string(char *dst, char *src);
char	*encoding(char *s);
int		decoding_fill_string(char *dst, char *src);
char	*decoding(char *s);
int		count_occurence(char *s);
int		count_only_one_occurence(char *s);
size_t	encoded_text_length(char *s);

#endif
