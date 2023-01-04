/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_red_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:39:32 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/03 23:47:12 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_bonus.h"

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

void	sort_red_str(t_str *list)
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
