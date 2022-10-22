/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:52:25 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 21:36:41 by hyanagim         ###   ########.fr       */
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
	if (is_redirection(str))
		return (false);
	return (true);
}

static void	branch_bra(t_node *p, bool *failed_flag)
{
	p->end_pos++;
	while (!is_bra(p->line[p->end_pos]))
		p->end_pos++;
	p->line[p->end_pos] = NULL;
	start_left(p);
	p->left = talloc(SUBSHELL, p);
	do_parse(p->left, failed_flag);
	start_right(p);
	if (p->line[p->end_pos] != NULL)
	{
		p->right = talloc(ARGUMENTS, p);
		do_parse(p->right, failed_flag);
	}
}

void	branch_arguments(t_node *p, bool *failed_flag)
{
	if (is_bra(p->line[p->end_pos]))
		branch_bra(p, failed_flag);
	else if (is_redirection(p->line[p->end_pos]))
	{
		p->left = talloc(REDIRECTION, p);
		do_parse(p->left, failed_flag);
		p->end_pos++;
		if (p->line[p->end_pos] == NULL)
			return ;
		p->end_pos++;
		if (p->line[p->end_pos] != NULL)
		{
			p->start_pos = p->end_pos;
			p->include_right = true;
			p->right = talloc(ARGUMENTS, p);
			do_parse(p->right, failed_flag);
		}
	}
	else
	{
		while (can_go_advance(p->line[p->end_pos]))
			p->end_pos++;
		if (is_redirection(p->line[p->end_pos]))
		{
			start_left(p);
			p->left = talloc(COMMAND, p);
			do_parse(p->left, failed_flag);
			p->start_pos = p->current_pos;
			p->end_pos = p->current_pos;
			p->include_right = true;
			p->right = talloc(ARGUMENTS, p);
			do_parse(p->right, failed_flag);
		}
		else
		{
			start_left(p);
			p->left = talloc(COMMAND, p);
			do_parse(p->left, failed_flag);
		}
	}
}
