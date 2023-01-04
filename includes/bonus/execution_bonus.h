/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:11:55 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/04 23:57:36 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_BONUS_H
# define EXECUTION_BONUS_H

# include	<stdio.h>
# include	<fcntl.h>
# include	<signal.h>
# include	<readline/readline.h>
# include	<errno.h>
# include	<dirent.h>
# include	"define.h"
# include	"builtin.h"
# include	"envs.h"

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
bool	check_path(char **path, char **command);
void	exec_command(t_vars *vars, char **command);
void	exec_command_child(t_vars *vars, t_list *comline, t_list **pids);
void	exec_comline(t_vars *vars, t_list *comline);
void	exec_lt(t_list *comline);
void	exec_ltlt(t_vars *vars, t_list *comline);
void	exec_gt(t_list *comline);
void	exec_gtgt(t_list *comline);
void	check_command(t_vars *vars, char ***command);
t_list	*check_comline(t_list *comline);
char	**check_asterisk(char **cmd);
void	delete_quote(char *str);
void	make_tmp_file(t_order *order);
void	change_file(t_vars *vars, t_list *comline);
void	check_envs_from_path(t_vars *vars, char **command);
bool	check_front(char *file, char *str);
bool	check_back(char *file, char *str);
bool	move_asterisk(char **file, size_t i, char **words);
bool	match_asterisk(char *file, char *str);
char	**clip_latter(char **cmd, size_t start);
char	**realloc_array(char **cmd, char *str);
DIR		*calldir(void);
int		check_file_and_open(t_order *order);
int		get_heredoc(t_list *comline);
void	heredoc_unlink(t_list *comline, t_list *end);

#endif
