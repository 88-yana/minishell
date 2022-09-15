/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:23:58 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/15 23:36:45 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../parser/parser.h"

# define TRUE 1
# define FALSE 0

typedef struct s_vars {
	t_tree	*tree;
	int		lexer_size;
	int		lexer_pos;
}	t_vars;

//typedef enum e_type {
//	PIPE,
//	COMMAND
//}	t_type;

//typedef enum e_com_type {
//	CD,
//	MKDIR,
//	LS
//}	t_com_type;

//typedef struct s_command {
//	t_com_type	type;
//	char		*buf;
//	char		*command;
//	char		*option;
//	int			has_opt;
//}	t_command;

#endif
