/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:29:15 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 20:39:04 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

void	branch_delimiter(t_node *p, bool *failed_flag)
{
	if (ft_strcmp(p->line[p->current_pos], "||") == 0)
		p->detail = OR;
	if (ft_strcmp(p->line[p->current_pos], "&&") == 0)
		p->detail = AND;
	p->line[p->current_pos] = NULL;
	p->left = talloc(COMMAND_LINE, p);
	do_parse(p->left, failed_flag);
	start_right(p);
	p->right = talloc(COMMAND_LINE, p);
	do_parse(p->right, failed_flag);
}
