/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:51:12 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 21:42:34 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"
#include	"../../../libft/libft.h"

void	branch_subshell(t_node *p, bool *failed_flag)
{
	p->end_pos++;
	p->start_pos = p->end_pos;
	p->left = talloc(COMMAND_LINE, p);
	do_parse(p->left, failed_flag);
}

void	traverse_subshell(t_node *p, t_list **list)
{
	t_list	**subshell;
	t_list	*shell;
	t_list	*list_ptr;
	size_t	i;

	subshell = traverse(p->left, list);
	shell = subshell[0];
	i = 1;
	while (subshell[i] != NULL)
	{
		ft_lstadd_back(&shell, subshell[i]);
		i++;
	}
	list_ptr = ft_lstnew(make_command(SUBSHELL, NULL, NULL, shell));
	list = realloc_list(list, list_ptr);
}
