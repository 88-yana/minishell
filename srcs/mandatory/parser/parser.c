/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:00:40 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 22:53:06 by hyanagim         ###   ########.fr       */
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

t_list	**realloc_list(t_list **list, t_list *ptr)
{
	t_list	**new;
	size_t	size;
	size_t	i;

	size = 0;
	while (list[size] != NULL)
		size++;
	new = malloc(sizeof(t_list *) * (size + 2));
	i = 0;
	while (i < size)
	{
		new[i] = list[i];
		i++;
	}
	new[size] = ptr;
	new[size + 1] = NULL;
	// free(list);
	return (new);
}



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
	{
		traverse_redirectrion(p, &list);
	}
	if (p->type == COMMAND)
	{
		char	**array;
		size_t	i;
		t_list	*list_ptr;
		while (p->line[p->end_pos] != NULL && !is_delimiter(p->line[p->end_pos]) && !is_bra(p->line[p->end_pos])
			&& !is_pipe(p->line[p->end_pos]) && !is_redirection(p->line[p->end_pos]))
			p->end_pos++;
		array = malloc(sizeof(char *) * (p->end_pos - p->start_pos + 1));
		if (array == NULL)
			; //後で書く。
		i = 0;
		while (i < p->end_pos - p->start_pos)
		{
			array[i] = ft_strdup(p->line[p->start_pos + i]);
			if (array[i] == NULL)
				; //後で書く。
			i++;
		}
		array[i] = NULL;
		list_ptr = ft_lstnew(make_command(COMMAND, array, NULL, NULL));
		list = realloc_list(list, list_ptr);
		// size_index(list, p, COMMAND);
	}

	return (list);
}
// //stringかなんかで，
// //p->left が NULL だったら，lstnew して，登りながら，lstadd していく。


void	listlcpy(t_list **dst, t_list **list, size_t dstsize)
{
	size_t	i;

	if (dstsize > 0)
	{
		i = 0;
		while (list[i] && i < dstsize - 1)
		{
			dst[i] = list[i];
			i++;
		}
		dst[i] = NULL;
	}
}

void	cmdjoin(t_list **list)
{
	size_t	i;

	i = 0;
	while (i < listlen(list) - 1)
	{
		if (((t_order *)list[i]->content)->type == COMMAND &&
			((t_order *)list[i + 1]->content)->type == COMMAND)
		{
			((t_order *)list[i]->content)->cmd = arrayjoin(((t_order *)list[i]->content)->cmd, ((t_order *)list[i + 1]->content)->cmd);
			listlcpy(&(list[i + 1]), &(list[i + 2]), listlen(list));
		}
		i++;
	}
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
	int i = 0;
	cmdjoin(list);
	maked_list = list[0];
	i = 1;
	while (list[i] != NULL)
	{
		ft_lstadd_back(&maked_list, list[i]);
		i++;
	}
	display_command(maked_list); //プリント
	return (maked_list);
}
