/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 19:10:46 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/01 19:14:14 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_bonus.h"

bool	check_lex(t_str	*current)
{
	while (current && current->next)
	{
		if (current->type == BRA && current->next->type == CKET)
			return (false);
		current = current->next;
	}
	return (true);
}
