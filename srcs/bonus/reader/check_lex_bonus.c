/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 19:10:46 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/03 19:35:35 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_bonus.h"

bool	check_bt(t_str *head)
{
	t_str	*current;

	current = head;
	while (current && current->next)
	{
		if (current->type == CKET && current->next->type == STR)
			return (false);
		current = current->next;
	}
	current = slistlast(head);
	while (current && current->prev)
	{
		if (current->type == BRA && current->prev->type == STR)
			return (false);
		current = current->prev;
	}
	return (true);
}

bool	check_lex(t_str	*head)
{
	t_str	*current;

	current = head;
	while (current && current->next)
	{
		if (current->type == BRA && current->next->type == CKET)
			return (false);
		current = current->next;
	}
	if (check_bt(head) == false)
		return (false);
	current = head;
	while (current)
	{
		if (current->type == PIPE && current->next == NULL)
			return (false);
		if (current->type == PIPE && current->prev == NULL)
			return (false);
		current = current->next;
	}
	return (true);
}
