/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:49:22 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 20:50:52 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

void	branch_pipe(t_node *p, bool *failed_flag)
{
	p->left = talloc(ARGUMENTS, p);
	do_parse(p->left, failed_flag);
	start_right(p);
	p->right = talloc(PIPED_LINE, p);
	do_parse(p->right, failed_flag);
}
