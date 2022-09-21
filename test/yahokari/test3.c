/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:23:07 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/21 17:36:38 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/wait.h>
#include	"../../libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	size_t	i;
	size_t	j;
	// ft_split(envp[0], '=');
	char	**str;
	char	**elem;

	i = 0;
	while (envp[i])
	{
		str = ft_split(envp[i], '=');
		printf("[%s] = ", str[0]);
		elem = ft_split(str[1], ':');
		j = 0;
		while (elem[j])
		{
			printf(" '%s'", elem[j]);
			j++;
		}
		printf(" \n");
		i++;
	}
	return (0);
}
