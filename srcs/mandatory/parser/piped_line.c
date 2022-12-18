/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:40:17 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/18 13:28:04 by hyanagim         ###   ########.fr       */
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
	if (is_pipe(str))
		return (false);
	return (true);
}

void	branch_piped_line(t_node *p, bool *failed_flag)
{
	while (1)
	{
		while (can_go_advance(p->line[p->end_pos]))
			p->end_pos++;
		if (is_bra(p->line[p->end_pos]))
			match_bra(p);
		if (p->line[p->end_pos] == NULL || is_pipe(p->line[p->end_pos]))
			break ;
	}
	if (is_pipe(p->line[p->end_pos]))
	{
		free(p->line[p->end_pos]);
		p->line[p->end_pos] = NULL;
		start_left(p);
		p->left = talloc(PIPE, p);
		do_parse(p->left, failed_flag);
	}
	if (p->line[p->end_pos] == NULL)
	{
		start_left(p);
		p->left = talloc(ARGUMENTS, p);
		do_parse(p->left, failed_flag);
	}
}
