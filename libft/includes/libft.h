/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:00:17 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/02 19:09:37 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

size_t			ft_strlen(const char *s);
char			*ft_realloc(char *s1, int lenght);
char			*ft_strnew(size_t size);
void			*ft_bzero(void *s, size_t n);
char			*ft_strncat(char *dest, const char *src, size_t n);
unsigned long	ft_strlcat(char *dest, const char *src, size_t size);
#endif
