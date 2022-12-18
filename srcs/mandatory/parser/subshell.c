/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:51:12 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/17 23:25:31 by hyanagim         ###   ########.fr       */
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

static void	free_array_char(char **array)
{
	int	i;

	i = 0;
	// while (array[i] != NULL)
	// {
	// 	free(array[i]);
	// 	i++;
	// }
	free(array);
}

void	free_list_double_ptr(t_list **list)
{
	size_t	i;

	i = 0;
	while (list[i] != NULL)
	{
		if (((t_order *)list[i]->content)->type == COMMAND)
			free_array_char(((t_order *)list[i]->content)->cmd);
		// if (((t_order *)list[i]->content)->type == SUBSHELL)
		// 	free_list(&((t_order *)list[i]->content)->shell);
		free((t_order *)list[i]->content);
		i++;
	}
}

t_list	**traverse_subshell(t_node *p)
{
	t_list	**subshell;
	t_list	*shell;
	t_list	*list_ptr;
	t_list	**list;
	size_t	i;

	list = NULL;
	shell = NULL;
	subshell = traverse(p->left);
	i = 0;
	while (subshell[i] != NULL)
	{
		ft_lstadd_back(&shell, subshell[i]);
		i++;
	}
	list_ptr = ft_lstnew(make_command(SUBSHELL, NULL, NULL, shell));
	list = realloc_list_free(list, list_ptr);
	// free(list_ptr);
	// while (subshell[i] != NULL)
	// 	free(subshell[i]);
	free(subshell);
	// free_list_double_ptr(subshell);
	return (list);
	// ft_lstclear(&list_ptr, free); // kari
}
