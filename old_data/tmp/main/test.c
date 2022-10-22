/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:24:06 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/03 18:02:08 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/envs.h"

char	*expand_env(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				printf("%d", g_status % 256);
			else
			{
				if (ft_isalpha(str[i]) || str[i] == '_')
				{
					j = 0;
					while (ft_isalnum(str[i + j]) || str[i] == '_')
					{
						j++;
					}
				}
			}
		}
		else
			printf("%c", str[i]);
		i++;
	}
}
