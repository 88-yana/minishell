/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 21:00:44 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/15 23:25:28 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<readline/readline.h>
# include	<readline/history.h>

typedef enum e_symbol {
	COMMAND_LINE,
	SEQUENCIAL_COMMANDS,
	PIPED_COMMANDS,
	COMMAND,
	ARGUMENTS,
	STRING,
	REDIRECTION
}	t_symbol;

typedef struct s_tree {
	t_symbol		type;
	char			*line;
	void			*elem;
	struct s_tree	*parent;
	struct s_tree	*child_left;
	struct s_tree	*child_right;
}	t_tree;

// <-- parser.c -->
void	handle_parser(t_tree *tree);

// <-- parser_utils.c -->
t_tree	*talloc(t_symbol symbol);

#endif
