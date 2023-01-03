/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:46:52 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/03 19:59:34 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_bonus.h"

t_str	*slistlast(t_str *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	slistadd(t_str **head, t_str *add)
{
	if (add == NULL)
	{
		free_slist(*head);
		exit(1);
	}
	if (*head == NULL)
		*head = add;
	else
	{
		add->prev = slistlast(*head);
		slistlast(*head)->next = add;
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

void	free_sliststr(t_str *start, t_str *last)
{
	t_str	*temp;
	t_str	*current;

	current = start;
	while (1)
	{
		temp = current->next;
		free(current);
		if (current == last)
			break ;
		current = temp;
	}
}

void	free_slistall(t_str *head)
{
	t_str	*temp;
	t_str	*current;

	current = head;
	while (1)
	{
		temp = current->next;
		free(current->str);
		free(current);
		current = temp;
		if (current == NULL)
			break ;
	}
}
