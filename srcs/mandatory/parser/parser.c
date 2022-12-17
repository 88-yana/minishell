/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:00:40 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/17 23:45:58 by hyanagim         ###   ########.fr       */
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

//traverse の引数にlistはいらない

t_list	**traverse(t_node *p)
{
	t_list	**list;

	list = NULL;
	if (p->type == COMMAND_LINE)
		list = traverse(p->left);
	if (p->type == SUBSHELL)
		list = traverse_subshell(p);
	if (p->type == DELIMITER)
		list = traverse_delimiter(p);
	if (p->type == PIPED_LINE)
		list = traverse(p->left);
	if (p->type == PIPE)
		list = traverse_pipe(p);
	if (p->type == ARGUMENTS)
		list = traverse_arguments(p);
	if (p->type == REDIRECTION)
		list = traverse_redirectrion(p);
	if (p->type == COMMAND)
		list = traverse_command(p);
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
	t_node	*root;
	t_list	**list;
	t_list	*maked_list;
	bool	failed_flag;
	size_t	i;

	root = malloc(sizeof(t_node));
	if (root == NULL)
		exit(1);
	root->line = array;
	failed_flag = false;
	init_root(root);
	if (check_array_redirect(array) == false)
		return (NULL);
	do_parse(root, &failed_flag);
	if (failed_flag)
		return (NULL);
	// system("leaks -q a.out");
	list = traverse(root);
	// system("leaks -q a.out");
	cmdjoin(list);
	maked_list = list[0];
	i = 1;
	while (list[i] != NULL)
	{
		ft_lstadd_back(&maked_list, list[i]);
		i++;
	}
	free_tree(root);
	free(root);
	free(list);
	return (maked_list);
}

// int	main(void)
// {
// 	t_list	*list;
// 	char	*array[16] = {"echo", "hello", "|", "grep", "h", "&&", "echo", "hello", ">", "test.txt", "||", "(", "ls", "-a", ")", NULL};
// 	// char	*array[5] = {"echo", "hello", ">", "test.txt", NULL};
// 	// char	*array[9] = {"echo", "hello", "|", "grep", "h", "|", "grep", "h", NULL};
// 	// char	*array[4] = {"(", "ls", ")", NULL};
// 	// char	*array[] = {"(", "echo", "hello", ")", ">", "text.txt", NULL};
// 	// char	*array[18] = {"(", "echo", "hello", ")", "|", "(", "ls", ")", "&&", "(", "echo", "hello", ")", NULL};
// 	// char	*array[3] = {"echo", "hello", NULL};
// 	// char	*array[2] = {"echo", NULL};
// 	// system("leaks -q a.out");
// 	list = parser(array);
// 	// system("leaks -q a.out");
// 	// ft_lstclear(&list, free);

// 	// free_list(list);
// 	display_command(list);
// 	system("leaks -q a.out");
// }
