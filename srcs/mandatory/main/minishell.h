/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:23:58 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/27 20:32:38 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>
# include	<unistd.h>
# include	<sys/wait.h>
# include	<stdbool.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../../libft/libft.h"

# define READ 0
# define WRITE 1

typedef enum e_type {
	COMMAND,
	SUBSHELL,
	PIPE,
	AND,
	OR,
	GTGT,
	GT,
	LTLT,
	LT
}	t_type;

typedef struct s_order {
	t_type	type;
	char	**cmd;
	size_t	pipe_num;
	int		read_fd;
	int		write_fd;
	int		next_read_fd;
	char	*file;
	t_list	*shell;
}	t_order;

typedef struct s_envs {
	char	*type;
	char	*value;
}	t_envs;

typedef struct s_vars {
	t_list	*comline;
	t_list	*pids;
	t_list	*envs_list;
}	t_vars;

#endif
