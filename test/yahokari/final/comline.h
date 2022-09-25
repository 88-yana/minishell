/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comline.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:57:54 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/25 17:41:36 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMLINE_H
# define COMLINE_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<fcntl.h>
# include	<stdbool.h>
# include	<string.h>
# include	<unistd.h>
# include	<sys/wait.h>
# include	<sys/types.h>
# include	<sys/wait.h>
# include	"../../../libft/libft.h"

# define ERR -1
# define NONE -1
# define FALSE 0
# define TRUE 1

# define READ 0
# define WRITE 1

# define CHILD 0

int	g_status;

// PIPE "|"
// AND "&&"
// OR "||"
// GTGT ">>"
// GT ">"
// LTLT "<<"
// LT "<"

typedef enum e_type {
	COMMAND,
	SHELL,
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
	int		read_fd;
	int		write_fd;
	int		next_read_fd;
	char	*file;
	t_list	*shell;
}	t_order;

typedef struct s_vars {
	t_list	*comline;
	t_list	*pids;
	char	**envp;
}	t_vars;

// <-- comline.c -->
void	exec_comline(t_vars *vars, t_list *comline);

// <-- piped_commands.c -->
void	exec_command_child(t_vars *vars, t_list *comline, t_list **pids);

// <-- piped_commands_utils.c -->
void	set_fd(t_list *comline);
void	duplicate_output(t_order *order);
void	close_fd_child(t_order *order);
void	close_fd_parent(t_order *order);

// <-- redirection.c -->
void	exec_lt(t_list *comline);
void	exec_gt(t_list *comline);
void	exec_gtgt(t_list *comline);

// <-- pid.c -->
void	create_pid_list(t_list **list, pid_t pid);
void	wait_pids(t_list **pids);

// <-- find.c -->
bool	is_next_type(t_list *comline, t_type type);
t_list	*find_next_delimiters(t_list *comline);
t_list	*find_nth_piped_commands(t_list *comline, size_t n);
t_list	*find_last_piped_commands(t_list *comline);

#endif
