/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:57:54 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/26 13:41:47 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define FALSE 0
# define TRUE 1

# define READ 0
# define WRITE 1

extern int	g_status;

// PIPE "|"
// AND "&&"
// OR "||"
// GTGT ">>"
// GT ">"
// LTLT "<<"
// LT "<"

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

typedef struct s_comline {
	t_type	type;
	char	**cmd;
	int		read_fd;
	int		write_fd;
	int		next_read_fd;
	int		count;
	char	*file;
	t_list	*shell;
}	t_comline;

typedef struct s_vars {
	t_list	*comline;
	char	**envp;
}	t_vars;

void	display_command(t_list *command_line);
bool	is_next_pipe(t_list *list);
t_list	*find_next_piped_commands(t_list *list);
t_list	*find_last_commands(t_list *list);
void	execute_shell(t_list *list, t_vars *vars);
void	execute_redirection(t_list *list, t_vars *vars);

#endif
