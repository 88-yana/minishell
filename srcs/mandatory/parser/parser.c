/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:00:40 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/21 01:46:06 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

#include	"../../../includes/debug.h"

void	do_parse(t_node *p, bool *failed_flag)
{
	if (p->type == COMMAND_LINE)
		branch_command_line(p, failed_flag);
	if (p->type == DELIMITER)
		branch_delimiter(p, failed_flag);
	if (p->type == PIPED_LINE)
		branch_piped_line(p, failed_flag);
	if (p->type == PIPE)
		branch_pipe(p, failed_flag);
	if (p->type == ARGUMENTS)
		branch_arguments(p, failed_flag);
	if (p->type == REDIRECTION)
		branch_redirection(p, failed_flag);
	if (p->type == SUBSHELL)
		branch_subshell(p, failed_flag);
	return ;
}

// リダイレクションとサブシェルの位置関係はいじれない

t_list	**traverse(t_node *p, t_list **list)
{
	if (p->type == COMMAND_LINE)
		list = traverse(p->left, list);
	if (p->type == SUBSHELL)
		traverse_subshell(p, &list);
	if (p->type == DELIMITER)
		traverse_delimiter(p, &list);
	if (p->type == PIPED_LINE)
		list = traverse(p->left, list);
	if (p->type == PIPE)
		traverse_pipe(p, &list);
	if (p->type == ARGUMENTS)
		traverse_arguments(p, &list);
	if (p->type == REDIRECTION)
		traverse_redirectrion(p, &list);
	if (p->type == COMMAND)
		traverse_command(p, &list);
	return (list);
}

void	init_root(t_node *root)
{
	root->type = COMMAND_LINE;
	root->array_size = 11;
	root->start_pos = 0;
	root->current_pos = 0;
	root->end_pos = 0;
	root->include_right = 0;
	root->index = 0;
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
}

bool	check_array_redirect(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		if (check_arguments(array[i]) == false)
		{
			ft_putendl_fd("syntax error unexpected token", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

t_list	*parser(char **array)
{
	t_node	root;
	t_list	**list;
	t_list	*maked_list;
	bool	failed_flag;
	size_t	i;

	root.line = array;
	failed_flag = false;
	init_root(&root);
	if (check_array_redirect(array) == false)
		return (NULL);
	do_parse(&root, &failed_flag);
	if (failed_flag)
		return (NULL);
	list = malloc(sizeof(t_list *) * 1);
	list[0] = NULL;
	list = traverse(&root, list);
	cmdjoin(list);
	maked_list = list[0];
	i = 1;
	while (list[i] != NULL)
	{
		ft_lstadd_back(&maked_list, list[i]);
		i++;
	}
	display_command(maked_list);
	// //ft_lstclear(list, free);
	// free_tree(&root);
	return (maked_list);
}

// int	main(void)
// {
// 	t_list	*list;
// 	// char	*array[16] = {"echo", "hello", "|", "grep", "h", "&&", "echo", "hello", ">", "test.txt", "||", "(", "ls", "-a", ")", NULL};
// 	char	*array[6] = {"echo", "hello", "|", "grep", "h", NULL};

// 	list = parser(array);
// 	// ft_lstclear(&list, free);
// 	system("leaks -q a.out");
// }
