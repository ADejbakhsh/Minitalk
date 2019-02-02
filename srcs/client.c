/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adejbakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:50:35 by adejbakh          #+#    #+#             */
/*   Updated: 2019/02/02 15:56:17 by adejbakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 3)
		return (0);
	if (argv[2][0] == '1')
			kill(atoi(argv[1]), SIGUSR1);
	if (argv[2][0] == '2')
		kill(atoi(argv[1]), SIGUSR2);
	printf("pid : %d\n",getpid());
	return (0);
}
