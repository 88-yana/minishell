/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:34:00 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 18:39:55 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static void	swap_list(t_list *list, t_list *next)
{
	t_order	*temp;

	temp = (t_order *)list->content;
	list->content = (t_order *)next->content;
	next->content = temp;
}

void	sort_red_cmd(t_list *list)
{
	t_order	*current;
	t_order	*next;

	while (list && list->next)
	{
		current = (t_order *)list->content;
		next = (t_order *)list->next->content;
		if (current->type == COMMAND)
			if (next && is_redirect(next->type))
				swap_list(list, list->next);
		list = list->next;
	}
}

bool	sort_shell_cmd(t_list *list)
{
	t_order	*current;
	t_order	*next;

	while (list && list->next)
	{
		current = (t_order *)list->content;
		next = (t_order *)list->next->content;
		if (is_redirect(current->type))
		{
			if (next && next->type == SUBSHELL)
			{
				printf("syntax error near unexpected token\n");
				return (false);
			}
		}
		if (current->type == SUBSHELL)
			if (next && is_redirect(next->type))
				swap_list(list, list->next);
		list = list->next;
	}
	return (true);
}
