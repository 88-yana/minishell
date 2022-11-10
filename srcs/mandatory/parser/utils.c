/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:15:54 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 22:53:11 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

void	match_bra(t_node *p)
{
	p->end_pos++;
	while (!is_bra(p->line[p->end_pos]))
		p->end_pos++;
	p->end_pos++;
}

void	start_right(t_node *p)
{
	p->start_pos = p->current_pos + 1;
	p->end_pos = p->current_pos + 1;
	p->include_right = true;
}

void	start_left(t_node *p)
{
	p->current_pos = p->end_pos;
	p->end_pos = p->start_pos;
}

t_type	convert_redirection(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (LT);
	if (ft_strcmp(str, ">") == 0)
		return (GT);
	if (ft_strcmp(str, ">>") == 0)
		return (GTGT);
	if (ft_strcmp(str, "<<") == 0)
		return (LTLT);
	return (COMMAND_LINE);
}