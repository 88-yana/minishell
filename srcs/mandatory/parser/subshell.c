/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:51:12 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 20:51:51 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

void	branch_subshell(t_node *p, bool *failed_flag)
{
	p->end_pos++;
	p->start_pos = p->end_pos;
	p->left = talloc(COMMAND_LINE, p);
	do_parse(p->left, failed_flag);
}
