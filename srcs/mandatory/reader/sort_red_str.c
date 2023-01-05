/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_red_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:39:32 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/05 16:35:52 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static void	swap_list(t_str *list, t_str *prev)
{
	t_str	temp;

	temp.type = list->type;
	temp.str = list->str;
	list->type = prev->type;
	list->str = prev->str;
	prev->type = temp.type;
	prev->str = temp.str;
}

static void	sort_one_red_str(t_str *list)
{
	t_str	*current;
	t_str	*prev;

	current = slistlast(list);
	while (current && current->prev)
	{
		prev = current->prev;
		if (is_redirect(current->type))
		{
			if (prev->type == STR)
				swap_list(current, current->prev);
		}
		current = current->prev;
	}
}

static int	cnt_slist(t_str *list)
{
	int	cnt;

	cnt = 0;
	while (list)
	{
		list = list->next;
		cnt++;
	}
	return (cnt);
}

void	sort_red_str(t_str *list)
{
	int	i;
	int	cnt;

	cnt = cnt_slist(list);
	i = 0;
	while (i < cnt)
	{
		sort_one_red_str(list);
		i++;
	}
}
