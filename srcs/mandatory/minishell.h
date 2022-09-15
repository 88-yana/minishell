/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:23:58 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/13 19:08:18 by yahokari         ###   ########.fr       */
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

typedef enum e_type {
	PIPE,
	COMMAND
}	t_type;

typedef enum e_com_type {
	CD,
	MKDIR,
	LS
}	t_com_type;

typedef struct s_command {
	t_com_type	type;
	char		*buf;
	char		*command;
	char		*option;
	int			has_opt;
}	t_command;

typedef struct s_tree {
	t_type			type;
	t_command		*elem;
	struct t_tree	*parent;
	struct t_tree	*left;
	struct t_tree	*right;
}	t_tree;

#endif
