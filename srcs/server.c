/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:43:27 by hben-yah          #+#    #+#             */
/*   Updated: 2019/02/02 22:31:00 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		main(int ac, char **av)
{
	char *s;
	char *d;
	char *f;

	if (ac == 2)
	{
		printf("\ntaille avant encodage : %zu\n\n", ft_strlen(av[1]));
		d = encoding(av[1]);
		s = d;
		while (*s)
		{
			printf("%d ", *s);
			++s;
		}
		printf("\ntaille apres encodage : %zu\n", ft_strlen(d));
		
		f = decoding(d);
		printf("\ndecode : -%s-\n", f);

		printf("\ntaille apres decodage : %zu\n", ft_strlen(f));

	}
	return (0);
}
