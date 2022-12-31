/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:46:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 16:56:07 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static t_str	*slistlast(t_str *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	slistadd(t_str **head, t_str *new)
{
	if (new == NULL)
	{
		free_slist(*head);
		exit(1);
	}
	if (*head == NULL)
		*head = new;
	else
	{
		new->prev = slistlast(*head);
		slistlast(*head)->next = new;
	}
}

void	free_slist(t_str *head)
{
	t_str	*temp;
	t_str	*current;

	current = head;
	while (1)
	{
		temp = current->next;
		free(current);
		current = temp;
		if (current == NULL)
			break ;
	}
}
