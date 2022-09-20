/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:57:54 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/20 20:28:04 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>
# include	<unistd.h>
# include	<sys/wait.h>
# include	"../../../libft/libft.h"

# define READ 0
# define WRITE 1

// PIPE "/"
// AND "&&"
// OR "||"

typedef enum e_type {
	COMMAND,
	SHELL,
	PIPE,
	AND,
	OR
}	t_type;

typedef struct s_pipe_fd {
	int	read_fd;
	int	write_fd;
	int	next_read_fd;
}	t_pipe_fd;

typedef struct s_comline {
	t_type	type;
	char	**cmd;
	//パイプなどで繋がれたコマンドをダブルポインタで表示
	// t_type == COMMAND -> cmd = {"cat Makefile", "wc -l", "NULL"}
	// t_type != COMMAND -> cmd = NULL
	t_list	*shell;
	//sub shellの最初のコマンドのポインタを設定
	// t_type == SHELL -> shell = &t_command_line
	// t_type != SHELL -> shell = NULL
	// struct s_command_line	*next;
}	t_comline;

void		execute_shell(t_list *list);
t_comline	*make_command(t_type type, char **cmd, t_list *shell);
size_t		count_pipes(t_list *shell);
void		display_command(t_list	*command_line);

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
