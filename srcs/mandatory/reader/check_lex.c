/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 19:10:46 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/03 18:43:51 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

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
