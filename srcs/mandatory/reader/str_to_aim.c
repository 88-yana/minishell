/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_aim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:54:43 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/05 16:41:04 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

bool	str_to_aim(t_str *current)
{
	t_str	*temp;

	while (current != NULL)
	{
		if (is_redirect(current->type))
		{
			if (current->next && current->next->type == STR)
			{
				current->next->type = AIM;
				current->str = current->next->str;
				temp = current->next;
				if (temp->next)
					temp->next->prev = current;
				if (temp)
					current->next = temp->next;
			}
			else
				return (false);
			free(temp);
		}
		current = current->next;
	}
	return (true);
}
