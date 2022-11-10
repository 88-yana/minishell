/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:42:23 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 20:47:38 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

void	branch_redirection(t_node *p, bool *failed_flag)
{
	p->current_pos = p->end_pos;
	p->end_pos++;
	if (p->line[p->end_pos] == NULL)
	{
		printf("%s\n", "error in redirection in do_parse");
		*failed_flag = 1;
		return ;
	}
}
	// p->current_pos = p->end_pos; //redirection