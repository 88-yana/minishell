/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:42:23 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/17 23:31:58 by hyanagim         ###   ########.fr       */
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

t_list	**traverse_redirectrion(t_node *p)
{
	t_list	*list_ptr;
	t_type	type;
	t_order	*temp;
	t_list	**list;

	list = NULL;
	type = convert_redirection(p->line[p->current_pos]);
	temp = make_command(type, NULL, p->line[p->current_pos + 1], NULL);
	list_ptr = ft_lstnew(temp);
	list = realloc_list_free(list, list_ptr);
	// free(list_ptr);
	return (list);
	// ft_lstclear(&list_ptr, free); // kari
}
