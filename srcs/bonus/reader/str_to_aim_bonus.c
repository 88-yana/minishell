/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_aim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:54:43 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 17:03:08 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_bonus.h"

bool	str_to_aim(t_str *lexical_line)
{
	while (lexical_line != NULL)
	{
		if (is_redirect(lexical_line->type))
		{
			if (lexical_line->next && lexical_line->next->type == STR)
				lexical_line->next->type = AIM;
			else
				return (false);
		}
		lexical_line = lexical_line->next;
	}
	return (true);
}
