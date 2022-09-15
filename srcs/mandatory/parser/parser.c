/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:56:25 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/15 21:33:25 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"parser.h"

void	handle_command_line(t_tree *tree)
{
	tree->child_left = talloc(PIPED_COMMANDS);
	handle_parser(tree->child_left);
	tree->child_right = NULL;
}

void	handle_piped_command(t_tree *tree)
{
	(void)tree;
}

void	handle_command(t_tree *tree)
{
	tree->child_left = talloc(ARGUMENTS);
	handle_parser(tree->child_left);
	tree->child_right = NULL;
}

void	handle_arguments(t_tree *tree)
{
	(void)tree;
}

void	handle_string(t_tree *tree)
{
	(void)tree;
}

void	handle_redirection(t_tree *tree)
{
	(void)tree;
}

void	handle_parser(t_tree *tree)
{
	if (tree->type == COMMAND_LINE)
		handle_command_line(tree);
	else if (tree->type == PIPED_COMMANDS)
		handle_piped_command(tree);
	else if (tree->type == COMMAND)
		handle_command(tree);
	else if (tree->type == ARGUMENTS)
		handle_arguments(tree);
	else if (tree->type == STRING)
		handle_string(tree);
	else if (tree->type == REDIRECTION)
		handle_redirection(tree);
}
