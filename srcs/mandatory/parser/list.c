/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:45:48 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 23:02:25 by hyanagim         ###   ########.fr       */
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

void	listlcpy(t_list **dst, t_list **list, size_t dstsize)
{
	size_t	i;

	if (dstsize > 0)
	{
		i = 0;
		while (list[i] && i < dstsize - 1)
		{
			dst[i] = list[i];
			i++;
		}
		dst[i] = NULL;
	}
}

void	cmdjoin(t_list **list)
{
	size_t	i;
	char	**a;
	char	**b;


	i = 0;
	while (i < listlen(list) - 1)
	{
		if (((t_order *)list[i]->content)->type == COMMAND
			&& ((t_order *)list[i + 1]->content)->type == COMMAND)
		{
			a = ((t_order *)list[i]->content)->cmd;
			b = ((t_order *)list[i + 1]->content)->cmd;
			((t_order *)list[i]->content)->cmd = arrayjoin(a, b);
			listlcpy(&(list[i + 1]), &(list[i + 2]), listlen(list));
		}
		i++;
	}
}
