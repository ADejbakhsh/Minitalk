/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adejbakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:50:35 by adejbakh          #+#    #+#             */
/*   Updated: 2019/02/02 20:13:33 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_cara_by_cara(char car, char *pid)
{
	int	a;

	a = 0;
	while (a < 8)
	{
		if (((car <<= 1) & 256) == 0)
			kill(atoi(pid), SIGUSR1);
		else
			kill(atoi(pid), SIGUSR2);
		usleep(50);
		++a;
	}
}


int main(int argc, char **argv)
{
	int	a;

	a = 0;
	if (argc != 3)
		return (0);
	while (argv[2][a])
		ft_cara_by_cara(argv[2][a++], argv[1]);
	return (0);
}
