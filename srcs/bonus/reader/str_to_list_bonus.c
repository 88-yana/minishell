/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:38:08 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/03 23:04:54 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_bonus.h"

static t_list	*ft_lstnewprev(void	*content)
{
	t_list	*list;

	if (content == NULL)
		exit (1);
	list = malloc(sizeof(t_list));
	if (list == NULL)
		exit(1);
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

static void	ft_lstadd_backprev(t_list **list, t_list *new)
{
	t_list	*last;

	if (new == NULL || list == NULL)
		exit (1);
	if (*list == NULL)
		*list = new;
	else
	{
		last = ft_lstlast(*list);
		last->next = new;
		new->prev = last;
	}
}

static t_order	*make_order(t_str	*current)
{
	t_order	*order;
	t_type	type;

	type = current->type;
	if (type == COMMAND)
		order = make_command(current->type, current->cmd, NULL, NULL);
	else if (type == GTGT || type == GT || type == LTLT || type == LT)
		order = make_command(current->type, NULL, current->str, NULL);
	else
		order = make_command(current->type, NULL, NULL, NULL);
	return (order);
}

t_list	*str_to_list(t_str *head)
{
	t_str	*current;
	t_list	*list;

	list = NULL;
	current = head;
	while (current != NULL)
	{
		ft_lstadd_backprev(&list, ft_lstnewprev(make_order(current)));
		current = current->next;
		if (current != NULL && current->type == AIM)
			current = current->next;
	}
	return (list);
}
