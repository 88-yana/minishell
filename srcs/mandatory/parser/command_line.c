/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:52:00 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 20:18:23 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

static bool	can_go_advance(char *str)
{
	if (str == NULL)
		return (false);
	if (is_delimiter(str))
		return (false);
	if (is_bra(str))
		return (false);
	return (true);
}

void	branch_command_line(t_node *p, bool *failed_flag)
{
	while (1)
	{
		while (can_go_advance(p->line[p->end_pos]))
			p->end_pos++;
		if (is_bra(p->line[p->end_pos]))
			match_bra(p);
		if (p->line[p->end_pos] == NULL || is_delimiter(p->line[p->end_pos]))
			break ;
	}
	if (p->line[p->end_pos] == NULL)
	{
		p->end_pos = p->start_pos;
		p->left = talloc(PIPED_LINE, p);
		do_parse(p->left, failed_flag);
	}
	if (is_delimiter(p->line[p->end_pos]))
	{
		p->current_pos = p->end_pos;
		p->end_pos = p->start_pos;
		p->left = talloc(DELIMITER, p);
		do_parse(p->left, failed_flag);
	}
}
