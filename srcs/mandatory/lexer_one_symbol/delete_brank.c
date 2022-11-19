/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_brank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:54:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/19 21:18:29 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer_one_symbol.h"

char	**delete_brank(char **array)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (array[i] != NULL)
	{
		if (array[i][0] == '\0' || ft_strcmp(array[i], "\"\"") == 0
			|| ft_strcmp(array[i], "\'\'") == 0)
		{
			j = i;
			free(array[i]);
			while (1)
			{
				array[j] = array[j + 1];
				if (array[j + 1] == NULL)
					break ;
				j++;
			}
			continue ;
		}
		i++;
	}
	return (array);
}
