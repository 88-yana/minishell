/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:56:25 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/16 01:52:26 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"parser.h"

void	get_next_token(t_vars *vars)
{
	vars->lexer_pos++;
}

bool	match(char *str, t_vars *vars)
{
	if (ft_strcmp(str, lexer[vars->lexer_pos]) == 0)
		return true;
	return false;
}

void	handle_command_line(t_tree *tree)
{
	tree->child_left = talloc(SEQUENCIAL_COMMANDS);
	handle_parser(tree->child_left);
	tree->child_right = NULL;
}

void	handle_piped_command(t_tree *tree)
{
	tree->child_left = talloc(COMMAND);
	handle_parser(tree->child_left);
	get_next_token(vars);
	if (match("|", vars))
	{
		tree->child_right = talloc(PIPED_COMMANDS);
		handle_parse(tree->child_right);
	}
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

// \nはなんなのか
/*
command_line ::=
	| sequencial_commands delimiter command_line
	| (sequencial_commands) delimiter command_line
	| sequencial_commands
	| (sequencial_commands)

delimiter ::=
	"&&"
	"||"

piped_commands ::=
	  command "|" piped_commands
	| command

sequencial_commands ::=
	  piped_commands delimiter sequencial_commands
	| piped_commands

command ::=
	  arguments

arguments ::=
	  redirection
	| redirection arguments
	| string
	| string arguments

string ::=
	  expandable <no_space> string
	| expandable
	| not_expandable <no_space> string
	| not_expandable
	| expandable_quoted <no_space> string
	| expandable_quoted

redirection ::=
	  "<" string
	| ">" string
	| ">>" string
	| "<<" string
*/


/*
command_line ::=
	  "\n"
	| sequencial_commands "\n"
	| (sequencial_commands)

delimiter ::=
	"&&"
	"||"

piped_commands ::=
	  command "|" piped_commands
	| command

sequencial_commands ::=
	  piped_commands delimiter sequencial_commands
	  piped_commands delimiter (sequencial_commands)
	  (sequencial_commands) delimiter sequencial_commands
	  (sequencial_commands) delimiter (sequencial_commands)
	| piped_commands

command ::=
	  arguments

arguments ::=
	  redirection
	| redirection arguments
	| string
	| string arguments

string ::=
	  expandable <no_space> string
	| expandable
	| not_expandable <no_space> string
	| not_expandable
	| expandable_quoted <no_space> string
	| expandable_quoted

redirection ::=
	  "<" string
	| ">" string
	| ">>" string
	| "<<" string
*/

/*
command_line ::=
	  "\n"
	| sequencial_commands delimiter "\n"
	| sequencial_commands "\n"

delimiter ::=
	  ";"

sequencial_commands ::=
	  piped_commands delimiter sequencial_commands
	| piped_commands

piped_commands ::=
	  command "|" piped_commands
	| command

command ::=
	  arguments

arguments ::=
	  redirection
	| redirection arguments
	| string
	| string arguments

string ::=
	  expandable <no_space> string
	| expandable
	| not_expandable <no_space> string
	| not_expandable
	| expandable_quoted <no_space> string
	| expandable_quoted

redirection ::=
	  "<" string
	| ">" string
	| ">>" string
	| "<<" string
*/