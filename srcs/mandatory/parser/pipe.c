/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:49:22 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/17 22:45:25 by hyanagim         ###   ########.fr       */
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

t_list	**traverse_pipe(t_node *p)
{
	t_list	**latter;
	t_list	*list_ptr;
	t_list	**list;

	list_ptr = ft_lstnew(make_command(PIPE, NULL, NULL, NULL));
	list = traverse(p->left);
	list = realloc_list_free(list, list_ptr);
	latter = malloc(sizeof(t_list *));
	latter[0] = NULL;
	latter = traverse(p->right);
	list = listjoin(list, latter);
	free(latter);
	return (list);
	// ft_lstclear(&list_ptr, free); // kari
}
