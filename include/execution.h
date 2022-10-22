/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:11:55 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/19 23:07:31 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include	"structure.h"
# include	"builtin.h"
# include	"envs.h"
# include	"redirection.h"
# include	<stdio.h>
# include	<fcntl.h>
# include	<signal.h>
# include	<readline/readline.h>
# include	<errno.h>

# define ERR -1
# define NONE -1

# define READ 0
# define WRITE 1

# define CHILD 0

bool	is_next_type(t_list *comline, t_type type);
t_list	*find_next_delimiters(t_list *comline);
t_list	*find_nth_piped_commands(t_list *comline, size_t n);
t_list	*find_last_piped_commands(t_list *comline);
void	wait_pids(t_list **pids);
void	create_pid_list(t_list **list, pid_t pid);
void	set_fd(t_list *comline);
void	duplicate_output(t_order *order);
void	close_fd_child(t_order *order);
void	close_fd_parent(t_order *order);
void	check_comline(t_list *comline);
void	check_path(char **path, char **command);
void	exec_command(t_vars *vars, char **command);
void	exec_command_child(t_vars *vars, t_list *comline, t_list **pids);
void	exec_comline(t_vars *vars, t_list *comline);

#endif