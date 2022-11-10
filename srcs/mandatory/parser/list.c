/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:45:48 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 22:07:07 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

size_t	listlen(t_list **list)
{
	size_t	i;

	i = 0;
	while (list[i] != NULL)
		i++;
	return (i);
}

t_list	**listjoin(t_list **list, t_list **latter)
{
	size_t	length;
	size_t	i;
	size_t	j;
	t_list	**new;

	length = listlen(list) + listlen(latter);
	new = malloc(sizeof(t_list *) * (length + 1));
	i = 0;
	while (list[i] != NULL)
	{
		new[i] = list[i];
		i++;
	}
	j = 0;
	while (latter[j] != NULL)
	{
		new[i + j] = latter[j];
		j++;
	}
	new[length] = NULL;
	return (new);
}
