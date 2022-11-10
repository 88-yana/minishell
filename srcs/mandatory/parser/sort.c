/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:06:47 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 22:24:09 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

static void	comswap(t_list **list, size_t i, size_t j)
{
	t_list	*temp;
	t_type	a;
	t_type	b;

	a = ((t_order *)list[i]->content)->type;
	b = ((t_order *)list[j]->content)->type;
	if (a > b)
	{
		temp = list[i];
		list[i] = list[j];
		list[j] = temp;
	}
}

t_list	**sort_list(t_list	**list)
{
	size_t	i;
	size_t	j;

	i = listlen(list);
	while (i > 1)
	{	
		j = 0;
		while (j < i - 1)
		{
			comswap(list, j, j + 1);
			j++;
		}
		i--;
	}
	return (list);
}
