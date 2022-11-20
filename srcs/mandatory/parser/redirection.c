/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:42:23 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/21 04:18:46 by hyanagim         ###   ########.fr       */
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

void	traverse_redirectrion(t_node *p, t_list ***list)
{
	t_list	*list_ptr;
	t_type	type;
	t_order	*temp;

	type = convert_redirection(p->line[p->current_pos]);
	temp = make_command(type, NULL, p->line[p->current_pos + 1], NULL);
	list_ptr = ft_lstnew(temp);
	*list = realloc_list_free(*list, list_ptr);
	// ft_lstclear(&list_ptr, free); // kari
}
