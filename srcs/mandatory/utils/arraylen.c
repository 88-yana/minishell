/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:20:32 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/19 21:04:45 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/utils.h"

size_t	arraylen(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**arrayjoin(char **arr1, char**arr2)
{
	size_t	length;
	size_t	i;
	size_t	j;
	char	**new;

	length = arraylen(arr1) + arraylen(arr2);
	new = malloc(sizeof(char *) * (length + 1));
	i = 0;
	while (arr1[i] != NULL)
	{
		new[i] = arr1[i];
		i++;
	}
	j = 0;
	while (arr2[j] != NULL)
	{
		new[i + j] = arr2[j];
		j++;
	}
	new[length] = NULL;
	i = 0;
	free(arr1);
	return (new);
}
