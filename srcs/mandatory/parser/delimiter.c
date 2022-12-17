/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:29:15 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/17 20:01:49 by hyanagim         ###   ########.fr       */
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

t_list	**traverse_delimiter(t_node *p, t_list **list)
{
	t_list	**latter;
	t_list	*list_ptr;

	if (p->detail == OR)
		list_ptr = ft_lstnew(make_command(OR, NULL, NULL, NULL));
	if (p->detail == AND)
		list_ptr = ft_lstnew(make_command(AND, NULL, NULL, NULL));
	list = traverse(p->left, list);
	list = realloc_list_free(list, list_ptr);
	latter = malloc(sizeof(t_list *));
	latter[0] = NULL;
	latter = traverse(p->right, latter);
	list = listjoin(list, latter);
	free(latter);
	return (list);
	// ft_lstclear(&list_ptr, free); // kari
}
