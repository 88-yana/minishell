/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 19:10:46 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/07 21:17:58 by hyanagim         ###   ########.fr       */
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

static bool	zengo(t_type type)
{
	if (type == STR)
		return (true);
	if (type == BRA)
		return (true);
	if (type == CKET)
		return (true);
	return (false);
}

static bool	check_zengo(t_type type, t_str *next, t_str *prev)
{
	if (prev == NULL || next == NULL)
	{
		if (type == PIPE)
			return (false);
		if (type == OR)
			return (false);
		if (type == AND)
			return (false);
	}
	if (type == PIPE || type == AND || type == OR)
	{
		if (!zengo(next->type))
			return (false);
		if (!zengo(prev->type))
			return (false);
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
		if (!check_zengo(current->type, current->next, current->prev))
			return (false);
		current = current->next;
	}
	return (true);
}
